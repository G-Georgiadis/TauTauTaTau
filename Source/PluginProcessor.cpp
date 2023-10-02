/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TauTauTaTauAudioProcessor::TauTauTaTauAudioProcessor()
    : maximumDelayInSamples(1),
    delayMs_L(*apvts.getRawParameterValue("DelayL")),
    delayMs_R(*apvts.getRawParameterValue("DelayR")),
    feedback_L(*apvts.getRawParameterValue("FBL")),
    feedback_R(*apvts.getRawParameterValue("FBR")),
    feedback_X(*apvts.getRawParameterValue("FBX")),
    dry(false),
    syncToMidi(true),
    delayLine_L(maximumDelayInSamples),
    delayLine_R(maximumDelayInSamples),
    tempo(120.0),
    noteDuration_L(QuarterNote),
    noteDuration_R(EighthNote),
    filter_L(),
    filter_R()
{
    apvts.addParameterListener("DelayL", this);
    apvts.addParameterListener("DelayR", this);
    apvts.addParameterListener("FBL", this);
    apvts.addParameterListener("FBR", this);
    apvts.addParameterListener("FBX", this);
    apvts.addParameterListener("SyncToMidi", this);
    apvts.addParameterListener("Dry", this);
}

TauTauTaTauAudioProcessor::~TauTauTaTauAudioProcessor()
{
}

//==============================================================================
const juce::String TauTauTaTauAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

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

double TauTauTaTauAudioProcessor::getTailLengthSeconds() const
{
    return 3.0;
}

int TauTauTaTauAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TauTauTaTauAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TauTauTaTauAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TauTauTaTauAudioProcessor::getProgramName (int index)
{
    return {};
}

void TauTauTaTauAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void TauTauTaTauAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    dsp::ProcessSpec spec{ sampleRate, samplesPerBlock, 1 };

    delayLine_L.prepare(spec);
    delayLine_R.prepare(spec);

    delayLine_L.setMaximumDelayInSamples(sampleRate * 30.f);
    delayLine_R.setMaximumDelayInSamples(sampleRate * 30.f);

    delayLine_L.setDelay(*apvts.getRawParameterValue("DelayL") * sampleRate);
    delayLine_R.setDelay(*apvts.getRawParameterValue("DelayR") * sampleRate);

    delayMs_L.reset(sampleRate, 0.05);
    delayMs_R.reset(sampleRate, 0.05);

    filter_L.setCoefficients(IIRCoefficients::makeLowPass(sampleRate, 500));
    filter_R.setCoefficients(IIRCoefficients::makeLowPass(sampleRate, 500));

    filter_L.reset();
    filter_R.reset();
}

void TauTauTaTauAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void TauTauTaTauAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    float delayedSample_L, delayedSample_R;
    const int sampleRate = getSampleRate();

    if (syncToMidi)
    {
        AudioPlayHead* audioPlayHead = getPlayHead();
        auto position = audioPlayHead->getPosition();
        if (position.hasValue()) // If the host returned something
        {
            Optional<double> bpm = position->getBpm();
            if (bpm.hasValue()) // If the host returned a bpm value
                tempo = *bpm;

            delayMs_L.setValue(getNoteDurationSeconds(tempo, noteDuration_L), true);
            delayMs_R.setValue(getNoteDurationSeconds(tempo, noteDuration_R), true);
        }
    }

    for (int sampleIndex = 0; sampleIndex < buffer.getNumSamples(); sampleIndex++)
    {
        delayedSample_L = delayLine_L.popSample(0, delayMs_L.getNextValue() * sampleRate, true);
        delayedSample_R = delayLine_R.popSample(0, delayMs_R.getNextValue() * sampleRate, true);

        auto currentSampleL = buffer.getSample(Channels::Left, sampleIndex);
        auto currentSampleR = buffer.getSample(Channels::Right, sampleIndex);

        filter_L.processSamples(&currentSampleL, 1);
        filter_R.processSamples(&currentSampleR, 1);

        delayLine_L.pushSample(0, buffer.getSample(Channels::Left, sampleIndex) + delayedSample_L * feedback_L.getNextValue() + delayedSample_R * feedback_X.getCurrentValue());
        delayLine_R.pushSample(0, buffer.getSample(Channels::Right, sampleIndex) + delayedSample_R * feedback_R.getNextValue() + delayedSample_L * feedback_X.getCurrentValue());

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

//==============================================================================
bool TauTauTaTauAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TauTauTaTauAudioProcessor::createEditor()
{
    //return new GenericAudioProcessorEditor(this);
    return new TauTauTaTauAudioProcessorEditor (*this);
}

//==============================================================================
void TauTauTaTauAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void TauTauTaTauAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(apvts.state.getType()))
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

float TauTauTaTauAudioProcessor::softclip(float value)
{
    value = 2 / MathConstants<float>::pi * atanf(value);

    return value;
}

AudioProcessorValueTreeState::ParameterLayout TauTauTaTauAudioProcessor::createParameterLayout()
{
    AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<AudioParameterFloat>("DelayL", "Delay L", 0.01f, 3.f, 0.25f));
    layout.add(std::make_unique<AudioParameterFloat>("DelayR", "Delay R", 0.01f, 3.f, 0.25f));

    layout.add(std::make_unique<AudioParameterFloat>("FBL", "Feedback L", NormalisableRange<float>(0.0f, 1.0f), 0.25f,
        AudioParameterFloatAttributes().withLabel("Feedback L").withStringFromValueFunction([](float value, int)
            {return String(value * 100.0f, 1) + "%";})));

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

float TauTauTaTauAudioProcessor::getNoteDurationSeconds(double tempo, NoteDuration noteDuration)
{
    constexpr auto secondsInMinute = 60;
    auto sixtyfourth = secondsInMinute / tempo / 16.0;
    switch (noteDuration)
    {
    case Bar8:
        return (float)8 * 64 * sixtyfourth;
    case Bar4:
        return (float)4 * 64 * sixtyfourth;
    case Bar3:
        return (float)3 * 64 * sixtyfourth;
    case Bar2:
        return (float)2 * 64 * sixtyfourth;
    case Bar:
        return (float)64 * sixtyfourth;
    case HalfNote:
        return (float)32 * sixtyfourth;
    case QuarterNote:
        return (float)16 * sixtyfourth;
    case EighthNote:
        return (float)8 * sixtyfourth;
    case SixteenthNote:
        return (float)4 * sixtyfourth;
    case ThirtysecondthNote:
        return (float)2 * sixtyfourth;
    caseSixtyfourthNote:
        return (float)sixtyfourth;
    }
}

void TauTauTaTauAudioProcessor::parameterChanged(const String& parameterID, float newValue)
{
    if (parameterID == "DelayL") delayMs_L.setTargetValue(newValue);
    if (parameterID == "DelayR") delayMs_R.setTargetValue(newValue);

    if (parameterID == "FBL") feedback_L.setTargetValue(newValue);
    if (parameterID == "FBR") feedback_R.setTargetValue(newValue);
    if (parameterID == "FBX") feedback_X.setTargetValue(newValue);

    if (parameterID == "SyncToMidi") syncToMidi = newValue == 0.f;  // syncToMidi will be true if newValue is not 0.f, flase if it is.

    if (parameterID == "Dry") dry = newValue;
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TauTauTaTauAudioProcessor();
}
