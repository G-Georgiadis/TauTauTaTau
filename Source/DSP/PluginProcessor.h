/*****************************************************************//**
 * \file   PluginProcessor.h
 * \brief  Definitions for the AudioProcesor of the plugin.
 * 
 * \author George Georgiadis
 * \date   October 2023
 *********************************************************************/

#pragma once

#include <JuceHeader.h>
#include "..\Constants.h"


using namespace juce;

/** The audio processing side of the plugin. */
class TauTauTaTauAudioProcessor  : public juce::AudioProcessor, AudioProcessorValueTreeState::Listener
{
    
public:
    /** Initializes the AudioProcessor. */
    TauTauTaTauAudioProcessor();

    //==============================================================================

    /** Returns the plugin name. */
    const juce::String getName() const override;

    // ToDo: Change this to return false if MIDI ió not finally used.
    /** Returns true. */
    bool acceptsMidi() const override;
    /** Returns false as MIDI out will not be needed. */
    bool producesMidi() const override;
    /** Returns false. */
    bool isMidiEffect() const override;

    /** Returns the length of the processor's tail, in seconds. */
    double getTailLengthSeconds() const override;

    /** Returns the number of programs (presets) - not currently used. */
    int getNumPrograms() override;
    /** Returns the current program number. Currently not implemented - returns 0. */
    int getCurrentProgram() override;
    /** Sets the program number to use. Currently not implemented. Does nothing. */
    void setCurrentProgram(int index) override;
    /** Returns the current program name. Not currently implemented - returns an empty juce::String object. */
    const juce::String getProgramName(int index) override;
    /** Changes the current program name. Not implemented - does nothing. */
    void changeProgramName(int index, const juce::String& newName) override;

    //==============================================================================

    /**
     * Called before playback starts, to let the processor prepare itself.
     * The sample rate is the target sample rate, and will remain constant until playback stops..
     * 
     * \param sampleRate:    the target sample rate.
     * \param samplesPerBlock:  a strong hint about the maximum number of samples that
     * will be provided in each block.
     * You may want to use this value to resize internal
     * buffers. You should program defensively in case a buggy host exceeds this value.
     * The actual block sizes that the host uses may be different each time the callback
     * happens: completely variable block sizes can be expected from some hosts.
     */
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    /** Called after playback has stopped, to let the object free up any resources it no longer needs. */
    void releaseResources() override;
    /**
     * Renders the next block.
     * When this method is called, the buffer contains a number of channels which is
     * at least as great as the maximum number of input and output channels that this
     * processor is using. It will be filled with the processor's input data and should
     * be replaced with the processor's output.
     */
    void processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) override;

    /** Creates the processor's GUI. */
    juce::AudioProcessorEditor* createEditor() override;
    /** Returns true if the plugin processor can create an editor component. */
    bool hasEditor() const override;

    //==============================================================================
    /** Writes the current state information on the given MemoryBlock. */
    void getStateInformation (juce::MemoryBlock& destData) override;
    /** Retrieves previously stored state from the data pointer. */
    void setStateInformation (const void* data, int sizeInBytes) override;

    /** Holds the current state of the AudioProcessor value tree. */
    AudioProcessorValueTreeState apvts{ *this, nullptr, "TauTauTaTauParameters", createParameterLayout() };

    /** "Squashes" sample values so that they don't exceed 1.f (0dBFS) */
    float softclip(float value);
private:
    /** Enum with the channel numbers as channel names */
    enum Channels
    {
        Left,
        Right
    };

    ///** Enum with the common note duration names. */
    //enum NoteDuration
    //{
    //    Bar8,
    //    Bar4,
    //    Bar3,
    //    Bar2,
    //    Bar,
    //    HalfNote,
    //    QuarterNote,
    //    EighthNote,
    //    SixteenthNote,
    //    ThirtysecondthNote,
    //    SixtyfourthNote
    //};

    /** Creates the parameter layout for the AudioProcessor value tree */
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    /** Initialized as 1 and set to the maximum delay in samples in prepareToPlay(). */
    int maximumDelayInSamples;

    /** Using SmoothedValues to avoid clicks. */
    /** Smoothed value for the left-channel delay time. */
    SmoothedValue<float> delaySec_L;
    /** Smoothed value for the right-channel delay time. */
    SmoothedValue<float> delaySec_R;

    /** Smoothed value for the left-channel feedback. */
    SmoothedValue<float> feedback_L;
    /** Smoothed value for the right-channel feedback. */
    SmoothedValue<float> feedback_R;
    /** Smoothed value for the cross feedback. */
    SmoothedValue<float> feedback_X;

    /** True = midi sync, false = seconds */
    bool syncToMidi;

    /** True = mix dry signal, false = don't. */
    bool dry;

    /** Left-cahnnel delay line. */
    dsp::DelayLine<float> delayLine_L;
    /** Right-cahnnel delay line. */
    dsp::DelayLine<float> delayLine_R;

    /** The current tempo if given by the host, 120.00 otherwise. */
    double tempo;

    /** Delay time as note duration for the left-channel. */
    String noteDuration_L;
    /** Delay time as note duration for the right-channel. */
    String noteDuration_R;

    /** Returns the note duration in seconds of the given tempo and note duration */
    float getNoteDurationSeconds(double tempo, String noteDuration);

    // Inherited via Listener
    void parameterChanged(const String& parameterID, float newValue) override;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TauTauTaTauAudioProcessor)
};
