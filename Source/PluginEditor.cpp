/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TauTauTaTauAudioProcessorEditor::TauTauTaTauAudioProcessorEditor (TauTauTaTauAudioProcessor& p)
    : AudioProcessorEditor (&p),
    audioProcessor (p),
    delay_L_Slider("Delay L"),
    delay_R_Slider("Delay R"),
    feedback_L_Slider("Feedback L"),
    feedback_X_Slider("X Feedback"),
    feedback_R_Slider("Feedback R"),
    delay_L_Slider_Attachment(p.apvts, "DelayL", delay_L_Slider),
    delay_R_Slider_Attachment(p.apvts, "DelayR", delay_R_Slider),
    feedback_L_Slider_Attachment(p.apvts, "FBL", feedback_L_Slider),
    feedback_X_Slider_Attachment(p.apvts, "FBX", feedback_X_Slider),
    feedback_R_Slider_Attachment(p.apvts, "FBR", feedback_R_Slider),
    gradient()

{
    setSize (400, 300);

    addAndMakeVisible(delay_L_Slider);
    addAndMakeVisible(delay_R_Slider);
    addAndMakeVisible(feedback_L_Slider);
    addAndMakeVisible(feedback_X_Slider);
    addAndMakeVisible(feedback_R_Slider);

    delay_L_Slider.setTextValueSuffix("sec");
    delay_R_Slider.setTextValueSuffix("sec");
    
}

TauTauTaTauAudioProcessorEditor::~TauTauTaTauAudioProcessorEditor()
{
}

//==============================================================================
void TauTauTaTauAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.setGradientFill(gradient);
    g.fillAll();
}

void TauTauTaTauAudioProcessorEditor::resized()
{
    auto localBounds = getLocalBounds();
    auto topBounds = localBounds.removeFromTop(localBounds.getHeight() * 0.5);

    delay_L_Slider.setBounds(topBounds.removeFromLeft(topBounds.getWidth() * 0.5));
    delay_R_Slider.setBounds(topBounds);

    auto feedbackKnobWidth = localBounds.getWidth() * 0.333;

    feedback_L_Slider.setBounds(localBounds.getX(), localBounds.getY(), feedbackKnobWidth, localBounds.getHeight());
    feedback_X_Slider.setBounds(feedbackKnobWidth, localBounds.getY(), feedbackKnobWidth, localBounds.getHeight());
    feedback_R_Slider.setBounds(feedbackKnobWidth * 2, localBounds.getY(), feedbackKnobWidth, localBounds.getHeight());

    gradient = ColourGradient(Colours::beige, localBounds.getBottomLeft().toFloat(), Colours::white, localBounds.getTopRight().toFloat(), false);
}
