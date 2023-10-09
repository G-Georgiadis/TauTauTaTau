/*****************************************************************//**
 * \file   PluginEditor.cpp
 * \brief  Defines the UI of the plugin.
 * \note	Comments are in the header file, or hover mouse over keyword if your IDE supports it.
 * 
 * \author George Georgiadis
 * \date   October 2023
 *********************************************************************/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TauTauTaTauAudioProcessorEditor::TauTauTaTauAudioProcessorEditor(TauTauTaTauAudioProcessor& p)
    : AudioProcessorEditor(&p),
    audioProcessor(p),
    delay_L_Slider("Delay L"),
    delay_R_Slider("Delay R"),
    delay_L_ComboBox(),
    delay_R_ComboBox(),
    feedback_L_Slider("Feedback L"),
    feedback_X_Slider("X Feedback"),
    feedback_R_Slider("Feedback R"),
    midiSyncSwitch(),
    dry_Button(),
    delay_L_Slider_Attachment(p.apvts, "DelayL", delay_L_Slider),
    delay_R_Slider_Attachment(p.apvts, "DelayR", delay_R_Slider),
    delay_L_ComboBox_Attachment(p.apvts, "NoteDurationL", delay_L_ComboBox),
    delay_R_ComboBox_Attachment(p.apvts, "NoteDurationR", delay_R_ComboBox),
    feedback_L_Slider_Attachment(p.apvts, "FBL", feedback_L_Slider),
    feedback_X_Slider_Attachment(p.apvts, "FBX", feedback_X_Slider),
    feedback_R_Slider_Attachment(p.apvts, "FBR", feedback_R_Slider),
    midiSyncSwitch_Attachment(p.apvts, "SyncToMidi", midiSyncSwitch),
    dry_Button_Attachment(p.apvts, "Dry", dry_Button),
    gradient()
{
    setSize (400, 300);

    addChildComponent(delay_L_Slider);
    addChildComponent(delay_R_Slider);

    addChildComponent(delay_L_ComboBox);
    addChildComponent(delay_R_ComboBox);

    addAndMakeVisible(feedback_L_Slider);
    addAndMakeVisible(feedback_X_Slider);
    addAndMakeVisible(feedback_R_Slider);
    addAndMakeVisible(midiSyncSwitch);
    addAndMakeVisible(dry_Button);

    delay_L_Slider.setTextValueSuffix("sec");
    delay_R_Slider.setTextValueSuffix("sec");
}

TauTauTaTauAudioProcessorEditor::~TauTauTaTauAudioProcessorEditor()
{
}


void TauTauTaTauAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.setGradientFill(gradient);
    g.fillAll();

    if (midiSyncSwitch.getToggleState())
    {   //MidiSync is enabled, show delay time drop downs
        /** Make the delay time knobs invisible if they are visible. */
        if (delay_L_Slider.isVisible()) delay_L_Slider.setVisible(false);
        if (delay_R_Slider.isVisible()) delay_R_Slider.setVisible(false);
        /** Make the combo boxes visible if they are not. */
        if (!delay_L_ComboBox.isVisible()) delay_L_ComboBox.setVisible(true);
        if (!delay_R_ComboBox.isVisible()) delay_R_ComboBox.setVisible(true);

    }
    else
    {   //MidiSync is disabled, show delays in Sec.
    /** Make the combo boxes invisible if they are visible. */
        if (delay_L_ComboBox.isVisible()) delay_L_ComboBox.setVisible(false);
        if (delay_R_ComboBox.isVisible()) delay_R_ComboBox.setVisible(false);
        /** Make the delay time knobs visible if they are not. */
        if (!delay_L_Slider.isVisible()) delay_L_Slider.setVisible(true);
        if (!delay_R_Slider.isVisible()) delay_R_Slider.setVisible(true);
    }
    
}

void TauTauTaTauAudioProcessorEditor::resized()
{
    /** Local bounds */
    auto localBounds = getLocalBounds();
    /** Top bounds rectangle */
    auto topBounds = localBounds.removeFromTop(localBounds.getHeight() * 0.5);

    /** Top bounds position */
    /** Top Bounds X */
    auto topBoundsX = topBounds.getX();
    /** Top Bounds Y */
    auto topBoundsY = topBounds.getY();
    /** Top Bounds Width */
    auto topBoundsWidth = topBounds.getWidth();
    /** Top bounds Height */
    auto topBoundsHeight = topBounds.getHeight();

    auto delay_L_Bounds = Rectangle<int>(topBoundsX, topBoundsY, topBoundsWidth * 0.46, topBoundsHeight);
    auto midiSyncSwitch_Bounds = Rectangle<int>(topBoundsWidth * 0.46, topBounds.getCentreY() - 20, topBoundsWidth * 0.08, 40);
    auto delay_R_Bounds = Rectangle<int>(topBoundsWidth * 0.54, topBoundsY, topBoundsWidth * 0.46, topBoundsHeight);

    delay_L_Slider.setBounds(delay_L_Bounds);
    delay_L_ComboBox.setBounds(delay_L_Bounds.reduced(5, (topBoundsHeight - Constants::DropDownMenus::DROP_DOWN_MENU_HEIGHT) / 2));
    midiSyncSwitch.setBounds(midiSyncSwitch_Bounds);
    delay_R_Slider.setBounds(delay_R_Bounds);
    delay_R_ComboBox.setBounds(delay_R_Bounds.reduced(5, (topBoundsHeight - Constants::DropDownMenus::DROP_DOWN_MENU_HEIGHT) / 2));

    auto feedbackKnobWidth = localBounds.getWidth() * 0.333;

    feedback_L_Slider.setBounds(localBounds.getX(), localBounds.getY(), feedbackKnobWidth, localBounds.getHeight());
    feedback_X_Slider.setBounds(feedbackKnobWidth, localBounds.getY(), feedbackKnobWidth, localBounds.getHeight());
    feedback_R_Slider.setBounds(feedbackKnobWidth * 2, localBounds.getY(), feedbackKnobWidth, localBounds.getHeight());

    dry_Button.setBounds(localBounds.getX() + 10, localBounds.getHeight() - 25, 30, 15);

    gradient = ColourGradient(Colours::beige, localBounds.getBottomLeft().toFloat(), Colours::white, localBounds.getTopRight().toFloat(), false);
}
