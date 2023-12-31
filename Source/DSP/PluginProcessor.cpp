/*****************************************************************//**
 * \file    PluginProcessor.cpp
 * \brief   The DSP implementeation of the plugin
 * \note	Comments are in the header file, or hover mouse over keyword if your IDE supports it.
 * 
 * \author George Georgiadis
 * \date   October 2023
 *********************************************************************/

#include "PluginProcessor.h"
#include <juce_dsp/juce_dsp.h>
#include "..\UI\PluginEditor.h"

//==============================================================================

TauTauTaTauAudioProcessor::TauTauTaTauAudioProcessor()
    : maximumDelayInSamples(1),
    delaySec_L(*apvts.getRawParameterValue("DelayL")),
    delaySec_R(*apvts.getRawParameterValue("DelayR")),
    feedback_L(*apvts.getRawParameterValue("FBL")),
    feedback_R(*apvts.getRawParameterValue("FBR")),
    feedback_X(*apvts.getRawParameterValue("FBX")),
    /*filterParams(),*/
    filter_L(),
    filter_R(),
    syncToMidi(true), 
    dry(false),
    delayLine_L(maximumDelayInSamples),
    delayLine_R(maximumDelayInSamples),
    tempo(120.0),
    noteDuration_L(Constants::DropDownMenus::NOTE_DURATIONS[static_cast<int>(*apvts.getRawParameterValue("NoteDurationL"))]),
    noteDuration_R(Constants::DropDownMenus::NOTE_DURATIONS[static_cast<int>(*apvts.getRawParameterValue("NoteDurationR"))])
{
    apvts.addParameterListener("DelayL", this);
    apvts.addParameterListener("DelayR", this);
    apvts.addParameterListener("NoteDurationL", this);
    apvts.addParameterListener("NoteDurationR", this);
    apvts.addParameterListener("FBL", this);
    apvts.addParameterListener("FBR", this);
    apvts.addParameterListener("FBX", this);
    apvts.addParameterListener("SyncToMidi", this);
    apvts.addParameterListener("Dry", this);
}

AudioProcessorValueTreeState::ParameterLayout TauTauTaTauAudioProcessor::createParameterLayout()
{
    AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<AudioParameterFloat>("DelayL", "Delay L", 0.01f, 3.f, 0.25f));
    layout.add(std::make_unique<AudioParameterFloat>("DelayR", "Delay R", 0.01f, 3.f, 0.25f));

    layout.add(std::make_unique<AudioParameterChoice>
        (
            "NoteDurationL",
            "Note Duration L",
            Constants::DropDownMenus::NOTE_DURATIONS,
            11  // 1/4
        ));
    layout.add(std::make_unique<AudioParameterChoice>
        (
            "NoteDurationR",
            "Note Duration R",
            Constants::DropDownMenus::NOTE_DURATIONS,
            14  // 1/8
        ));

    layout.add(std::make_unique<AudioParameterFloat>("FBL", "Feedback L", NormalisableRange<float>(0.0f, 1.0f), 0.25f,
        AudioParameterFloatAttributes().withLabel("Feedback L").withStringFromValueFunction([](float value, int)
            {return String(value * 100.0f, 1) + "%"; })));

    layout.add(std::make_unique<AudioParameterFloat>("FBR", "Feedback R", NormalisableRange<float>(0.0f, 1.0f), 0.25f,
        AudioParameterFloatAttributes().withLabel("Feedback R").withStringFromValueFunction([](float value, int)
            {return String(value * 100.0f, 1) + "%"; })));

    layout.add(std::make_unique<AudioParameterFloat>("FBX", "Cross Feedback", NormalisableRange<float>(0.0f, 1.0f), 0.25f,
        AudioParameterFloatAttributes().withLabel("X Feedback").withStringFromValueFunction([](float value, int)
            {return String(value * 100.0f, 1) + "%"; })));

    layout.add(std::make_unique<AudioParameterBool>("SyncToMidi", "MIDI Sync", true));

    layout.add(std::make_unique<AudioParameterBool>("Dry", "Dry", false, AudioParameterBoolAttributes().withLabel("Dry")));

    return layout;
}

//==============================================================================
#pragma region The standard stuff
//==============================================================================

const juce::String TauTauTaTauAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

//==============================================================================

bool TauTauTaTauAudioProcessor::acceptsMidi() const
{
    return true;
}

bool TauTauTaTauAudioProcessor::producesMidi() const
{
    return false;
}

bool TauTauTaTauAudioProcessor::isMidiEffect() const
{
    return false;
}

//==============================================================================

double TauTauTaTauAudioProcessor::getTailLengthSeconds() const
{
    return 3.0;
}

//==============================================================================

int TauTauTaTauAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int TauTauTaTauAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TauTauTaTauAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String TauTauTaTauAudioProcessor::getProgramName(int index)
{
    return {};
}

void TauTauTaTauAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}
//==============================================================================
juce::AudioProcessorEditor* TauTauTaTauAudioProcessor::createEditor()
{
    //return new GenericAudioProcessorEditor(this);
    return new TauTauTaTauAudioProcessorEditor(*this);
}

bool TauTauTaTauAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

//==============================================================================

void TauTauTaTauAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void TauTauTaTauAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(apvts.state.getType()))
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}
#pragma endregion

//==============================================================================
#pragma region DSP
//=========================Inherited===========================================

void TauTauTaTauAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    using namespace Constants::DSP;

    dsp::ProcessSpec spec{ sampleRate, samplesPerBlock, 1 };

    delayLine_L.prepare(spec);
    delayLine_R.prepare(spec);

    delayLine_L.setMaximumDelayInSamples(sampleRate * MAXIMUM_DELAY_IN_SAMPLES);    // MAXIMUM_DELAY_IN_SAMPLES can be set in Constant.h
    delayLine_R.setMaximumDelayInSamples(sampleRate * MAXIMUM_DELAY_IN_SAMPLES);

    delayLine_L.setDelay(*apvts.getRawParameterValue("DelayL") * sampleRate);
    delayLine_R.setDelay(*apvts.getRawParameterValue("DelayR") * sampleRate);

    delaySec_L.reset(sampleRate, 0.05);
    delaySec_R.reset(sampleRate, 0.05);
    
    
    //filterParams.type = dsp::StateVariableFilter::StateVariableFilterType::lowPass;
    //filterParams.setCutOffFrequency(sampleRate, 250);

    filter_L.parameters.get()->type = dsp::StateVariableFilter::StateVariableFilterType::lowPass;
    filter_R.parameters.get()->type = dsp::StateVariableFilter::StateVariableFilterType::lowPass;

    filter_L.parameters.get()->setCutOffFrequency(sampleRate, 1000);
    filter_R.parameters.get()->setCutOffFrequency(sampleRate, 1000);

    filter_L.prepare(spec);
    filter_R.prepare(spec);
}

void TauTauTaTauAudioProcessor::releaseResources()
{
    
}

void TauTauTaTauAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    float delayedSample_L, delayedSample_R;
    const int sampleRate = getSampleRate();

    if (syncToMidi)
    {
        /** Get a poimter to the host play head */
        AudioPlayHead* audioPlayHead = getPlayHead();
        /** Attempt to get the play head position. */
        auto position = audioPlayHead->getPosition();
        /** Check if the host returned position information. */
        if (position.hasValue()) // If the host returned position information
        {
            /** Attempt to get the tempo from the host. */
            Optional<double> bpm = position->getBpm();
            /** Check if the host returned the tempo. */
            if (bpm.hasValue()) // If the host returned a bpm value
                /** Store the tempo for later use. */
                tempo = static_cast<double>(*bpm);
            /** Set the delay times according to tempo and the selected note duration. */
            delaySec_L.setTargetValue(getNoteDurationSeconds(noteDuration_L));
            delaySec_R.setTargetValue(getNoteDurationSeconds(noteDuration_R));
        }
    }

    /** Process the buffer sample-by-sample. */
    for (int sampleIndex = 0; sampleIndex < buffer.getNumSamples(); sampleIndex++)
    {
        /** Get the delayed samples. */
        delayedSample_L = delayLine_L.popSample(0, delaySec_L.getNextValue() * sampleRate, true);
        delayedSample_R = delayLine_R.popSample(0, delaySec_R.getNextValue() * sampleRate, true);

        /** Get the current samples */
        auto currentSampleL = buffer.getSample(Channels::Left, sampleIndex);
        auto currentSampleR = buffer.getSample(Channels::Right, sampleIndex);
        

        ///** Feedback Loop procesing. */
        delayedSample_L = filter_L.processSample(delayedSample_L);
        delayedSample_R = filter_R.processSample(delayedSample_R);

        // Apply feedback
        delayedSample_L = delayedSample_L * feedback_L.getNextValue() + delayedSample_R * feedback_X.getCurrentValue();
        delayedSample_R = delayedSample_R * feedback_R.getNextValue() + delayedSample_L * feedback_X.getCurrentValue();

        // Update the delay lines
        delayLine_L.pushSample(0, currentSampleL + delayedSample_L);
        delayLine_R.pushSample(0, currentSampleR + delayedSample_R);

        /** Write the results to the buffer. */
        if (dry)
        {
            buffer.addSample(Channels::Left, sampleIndex, softclip(delayedSample_L));
            buffer.addSample(Channels::Right, sampleIndex, softclip(delayedSample_R));
        }
        else
        {
            buffer.setSample(Channels::Left, sampleIndex, softclip(delayedSample_L));
            buffer.setSample(Channels::Right, sampleIndex, softclip(delayedSample_R));
        }
    }
}

//=========================Own==================================================

float TauTauTaTauAudioProcessor::softclip(float value)
{
    //if (value < -0.636 || value > 0.636)    // +-0.636 is the point when y=x (no softclipping) touches the softclip curve.
    //{
    //    value = (2.f / MathConstants<float>::pi) * 1.35 * atanf(pow(value, 0.2f));    // 1.35 is the vert. scalling factor & 0.2f is the exponent of the value
    //}
    //return value;
    value = 2 / MathConstants<float>::pi * atanf(value);

    return value;
}
#pragma endregion

//==============================================================================



float TauTauTaTauAudioProcessor::getNoteDurationSeconds(String noteDuration)
{
    constexpr auto secondsInMinute = 60.0;
    auto bar = 4 * secondsInMinute / tempo;
    auto dottedFactor = 1.5;
    auto tripletFactor = 2.0 / 3.0;
    auto sixtyfourth = secondsInMinute / tempo / 16.0;

    if (noteDuration == "8 Bars") return 8.0 * bar;
    if (noteDuration == "6 Bars") return 6.0 * bar;
    if (noteDuration == "5 Bars") return 5.0 * bar;
    if (noteDuration == "4 Bars") return 4.0 * bar;
    if (noteDuration == "3 Bars") return 3.0 * bar;
    if (noteDuration == "2 Bars") return 2.0 * bar;
    if (noteDuration == "1 Bar") return bar;
    if (noteDuration == "1/2d") return (1.0 / 2.0) * dottedFactor * bar;
    if (noteDuration == "1/2") return (1.0 / 2.0) * bar;
    if (noteDuration == "1/2t") return (1.0 / 2.0) * tripletFactor * bar;
    if (noteDuration == "1/4d") return (1.0 / 4.0) * dottedFactor * bar;
    if (noteDuration == "1/4") return (1.0 / 4.0) * bar;
    if (noteDuration == "1/4t") return (1.0 / 4.0) * tripletFactor * bar;
    if (noteDuration == "1/8d") return (1.0 / 8.0) * dottedFactor * bar;
    if (noteDuration == "1/8") return (1.0 / 8.0) * bar;
    if (noteDuration == "1/8t") return (1.0 / 8.0) * tripletFactor * bar;
    if (noteDuration == "1/16d") return (1.0 / 16.0) * dottedFactor * bar;
    if (noteDuration == "1/16") return (1.0 / 16.0) * bar;
    if (noteDuration == "1/16t") return (1.0 / 16.0) * tripletFactor * bar;
    if (noteDuration == "1/32d") return (1.0 / 32.0) * dottedFactor * bar;
    if (noteDuration == "1/32") return (1.0 / 32.0) * bar;
    if (noteDuration == "1/32t") return (1.0 / 32.0) * tripletFactor * bar;
    if (noteDuration == "1/64d") return (1.0 / 64.0) * dottedFactor * bar;
    if (noteDuration == "1/64") return (1.0 / 64.0) * bar;
    if (noteDuration == "1/64t") return (1.0 / 64.0) * tripletFactor * bar;
}

void TauTauTaTauAudioProcessor::parameterChanged(const String& parameterID, float newValue)
{
    if (parameterID == "DelayL") delaySec_L.setTargetValue(newValue);
    else if (parameterID == "DelayR") delaySec_R.setTargetValue(newValue);

    else if (parameterID == "NoteDurationL")
    {
        noteDuration_L = Constants::DropDownMenus::NOTE_DURATIONS[static_cast<int>(newValue)];
        //apvts.getParameter("DelayL")->setValue(getNoteDurationSeconds(tempo, noteDuration_L));
        apvts.getParameterAsValue("DelayL").setValue(newValue);
    }
    else if (parameterID == "NoteDurationR")
    {
        noteDuration_R = Constants::DropDownMenus::NOTE_DURATIONS[static_cast<int>(newValue)];
        //apvts.getParameter("DelayR")->setValue(getNoteDurationSeconds(tempo, noteDuration_R));
        apvts.getParameterAsValue("DelayR").setValue(newValue);
    }

    else if (parameterID == "FBL") feedback_L.setTargetValue(newValue);
    else if (parameterID == "FBR") feedback_R.setTargetValue(newValue);
    else if (parameterID == "FBX") feedback_X.setTargetValue(newValue);

    else if (parameterID == "SyncToMidi")
    {
        syncToMidi = newValue != 0.f;  // syncToMidi will be true if newValue is anything but 0.0, flase if it is 0.0.
        apvts.getParameterAsValue("DelayL").setValue(getNoteDurationSeconds(noteDuration_L));
        apvts.getParameterAsValue("DelayR").setValue(getNoteDurationSeconds(noteDuration_R));
    }

    else if (parameterID == "Dry") dry = newValue;
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TauTauTaTauAudioProcessor();
}
