#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TauTauTaTauAudioProcessorEditor::TauTauTaTauAudioProcessorEditor(TauTauTaTauAudioProcessor& p)
    : AudioProcessorEditor(&p),
    audioProcessor(p),
    delay_L_Slider("Delay L"),
    delay_R_Slider("Delay R"),
    feedback_L_Slider("Feedback L"),
    feedback_X_Slider("X Feedback"),
    feedback_R_Slider("Feedback R"),
    midiSyncSwitch(),
    dry_Button(),
    delay_L_Slider_Attachment(p.apvts, "DelayL", delay_L_Slider),
    delay_R_Slider_Attachment(p.apvts, "DelayR", delay_R_Slider),
    feedback_L_Slider_Attachment(p.apvts, "FBL", feedback_L_Slider),
    feedback_X_Slider_Attachment(p.apvts, "FBX", feedback_X_Slider),
    feedback_R_Slider_Attachment(p.apvts, "FBR", feedback_R_Slider),
    midiSyncSwitch_Attachment(p.apvts, "SyncToMidi", midiSyncSwitch),
    dry_Button_Attachment(p.apvts, "Dry", dry_Button),
    gradient()

{
    setSize (400, 300);

    addAndMakeVisible(delay_L_Slider);
    addAndMakeVisible(delay_R_Slider);
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
    midiSyncSwitch.setBounds(midiSyncSwitch_Bounds);
    delay_R_Slider.setBounds(delay_R_Bounds);

    auto feedbackKnobWidth = localBounds.getWidth() * 0.333;

    feedback_L_Slider.setBounds(localBounds.getX(), localBounds.getY(), feedbackKnobWidth, localBounds.getHeight());
    feedback_X_Slider.setBounds(feedbackKnobWidth, localBounds.getY(), feedbackKnobWidth, localBounds.getHeight());
    feedback_R_Slider.setBounds(feedbackKnobWidth * 2, localBounds.getY(), feedbackKnobWidth, localBounds.getHeight());

    

    dry_Button.setBounds(localBounds.getX() + 10, localBounds.getHeight() - 25, 30, 15);

    gradient = ColourGradient(Colours::beige, localBounds.getBottomLeft().toFloat(), Colours::white, localBounds.getTopRight().toFloat(), false);
}
