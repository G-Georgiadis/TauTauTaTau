#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "IndentedWheelSlider.h"

using namespace juce;

class TauTauTaTauAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    TauTauTaTauAudioProcessorEditor (TauTauTaTauAudioProcessor&);
    ~TauTauTaTauAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TauTauTaTauAudioProcessor& audioProcessor;

    IndentedWheelSlider delay_L_Slider;
    IndentedWheelSlider delay_R_Slider;

    IndentedWheelSlider feedback_L_Slider;
    IndentedWheelSlider feedback_X_Slider;
    IndentedWheelSlider feedback_R_Slider;
    

    AudioProcessorValueTreeState::SliderAttachment delay_L_Slider_Attachment;
    AudioProcessorValueTreeState::SliderAttachment delay_R_Slider_Attachment;
    
    AudioProcessorValueTreeState::SliderAttachment feedback_L_Slider_Attachment;
    AudioProcessorValueTreeState::SliderAttachment feedback_X_Slider_Attachment;
    AudioProcessorValueTreeState::SliderAttachment feedback_R_Slider_Attachment;

    ColourGradient gradient;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TauTauTaTauAudioProcessorEditor)
};
