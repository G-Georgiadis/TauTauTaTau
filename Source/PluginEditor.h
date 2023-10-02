#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "IndentedWheelSlider.h"
#include "DryButton.h"
#include "MidiSyncSwitch.h"

using namespace juce;

class TauTauTaTauAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    TauTauTaTauAudioProcessorEditor (TauTauTaTauAudioProcessor&);
    ~TauTauTaTauAudioProcessorEditor() override;

    
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    TauTauTaTauAudioProcessor& audioProcessor;

    IndentedWheelSlider delay_L_Slider;
    IndentedWheelSlider delay_R_Slider;

    IndentedWheelSlider feedback_L_Slider;
    IndentedWheelSlider feedback_X_Slider;
    IndentedWheelSlider feedback_R_Slider;

    MidiSyncSwitch midiSyncSwitch;

    DryButton dry_Button;
    

    AudioProcessorValueTreeState::SliderAttachment delay_L_Slider_Attachment;
    AudioProcessorValueTreeState::SliderAttachment delay_R_Slider_Attachment;
    
    AudioProcessorValueTreeState::SliderAttachment feedback_L_Slider_Attachment;
    AudioProcessorValueTreeState::SliderAttachment feedback_X_Slider_Attachment;
    AudioProcessorValueTreeState::SliderAttachment feedback_R_Slider_Attachment;

    AudioProcessorValueTreeState::ButtonAttachment midiSyncSwitch_Attachment;

    AudioProcessorValueTreeState::ButtonAttachment dry_Button_Attachment;


    ColourGradient gradient;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TauTauTaTauAudioProcessorEditor)
};
