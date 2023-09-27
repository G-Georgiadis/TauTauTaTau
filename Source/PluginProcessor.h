#pragma once

#include <JuceHeader.h>

using namespace juce;

class TauTauTaTauAudioProcessor  : public juce::AudioProcessor, AudioProcessorValueTreeState::Listener
{
    
public:
    TauTauTaTauAudioProcessor();
    ~TauTauTaTauAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;


    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    
    const juce::String getName() const override;


    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    AudioProcessorValueTreeState apvts{ *this, nullptr, "TauTauTaTauParameters", createParameterLayout() };
    double getTempo() const;
private:
    enum Channels
    {
        Left,
        Right
    };

    Optional<juce::AudioPlayHead::PositionInfo> currentPositionInfo;
    double tempo;
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    int maximumDelayInSamples;

    SmoothedValue<float> delayMs_L, delayMs_R;
    SmoothedValue<float> feedback_L, feedback_R, feedback_X;

    dsp::DelayLine<float> delayLine_L, delayLine_R;

    // Inherited via Listener
    void parameterChanged(const String& parameterID, float newValue) override;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TauTauTaTauAudioProcessor)
};
