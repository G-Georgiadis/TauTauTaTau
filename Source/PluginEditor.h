/*****************************************************************//**
 * \file   PluginEditor.h
 * \brief  Top-level definitions for the UI part of the plugin.
 * 
 * \author George Georgiadis
 * \date   October 2023
 *********************************************************************/
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

    /** Draws the UI background */
    void paint (juce::Graphics&) override;
    /** Sets the sizes and locations of components. */
    void resized() override;

private:
    /** A reference to the AudioProcessor of the plugin. */
    TauTauTaTauAudioProcessor& audioProcessor;
    /** Rotary slider controlling the left-channel delay time. */
    IndentedWheelSlider delay_L_Slider;
    /** Rotary slider controlling the right-channel delay time. */
    IndentedWheelSlider delay_R_Slider;
    
    /** Rotary slider controlling left-channel feedback. */
    IndentedWheelSlider feedback_L_Slider;
    /** Rotary slider controlling cross feedback. */
    IndentedWheelSlider feedback_X_Slider;
    /** Rotary slider controlling right-channel feedback. */
    IndentedWheelSlider feedback_R_Slider;

    /** 2-state switch for switching delay times between Seconds and note durations */
    MidiSyncSwitch midiSyncSwitch;

    /** 2-state button controlling if the dry signal is to be mixed with the effect signal. */
    DryButton dry_Button;
    
    /** Slider attachment connecting the left-channel delay time parameter with the respective rotary slider. */
    AudioProcessorValueTreeState::SliderAttachment delay_L_Slider_Attachment;
    /** Slider attachment connecting the right-channel delay time parameter with the respective rotary slider. */
    AudioProcessorValueTreeState::SliderAttachment delay_R_Slider_Attachment;
    
    /** Slider attachment connecting the left-channel feedback parameter with the respective rotary slider. */
    AudioProcessorValueTreeState::SliderAttachment feedback_L_Slider_Attachment;
    /** Slider attachment connecting the cross feedback parameter with the respective rotary slider. */
    AudioProcessorValueTreeState::SliderAttachment feedback_X_Slider_Attachment;
    /** Slider attachment connecting the right-channel feedback parameter with the respective rotary slider. */
    AudioProcessorValueTreeState::SliderAttachment feedback_R_Slider_Attachment;

    /** Button attachment connecting the midi sync parameter with the respective switch. */
    AudioProcessorValueTreeState::ButtonAttachment midiSyncSwitch_Attachment;
    /** Button attachment connecting the dry parameter with the respective button. */
    AudioProcessorValueTreeState::ButtonAttachment dry_Button_Attachment;

    /** The colour gradient used for the plugin background. */
    ColourGradient gradient;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TauTauTaTauAudioProcessorEditor)
};
