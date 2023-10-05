/*****************************************************************//**
 * \file	IndentedWheelSlider_LookAndFeel.cpp
 * \brief	Defines how the IndentedWheelSlider looks and interacts.
 * \note	Comments are in the header file, or hover mouse over keyword if your IDE supports it.
 * 
 * \author	George Georgiadis
 * \date	October 2023
 *********************************************************************/

#include "IndentedWheelSlider_LookAndFeel.h"

IndentedWheelSlider_LookAndFeel::IndentedWheelSlider_LookAndFeel(const String newTitleText)
	: side(0),
	halfSide(0),
	normalGradient(),
	reverseGradient(),
	colourGradientsInitialized(false),
	valueIndicator(),
	titleText(newTitleText)
{	
}

Slider::SliderLayout IndentedWheelSlider_LookAndFeel::getSliderLayout(Slider& slider)
{
	Slider::SliderLayout layout;

	Rectangle<int> localBounds = slider.getLocalBounds();
	layout.sliderBounds = localBounds;
	/** The textbox bounds are reduced so that text doesn't overlay the innerbevel because it looks bad. */
	layout.textBoxBounds = localBounds.reduced(0.2 * localBounds.getWidth(), 0.4f * localBounds.getHeight());
	/** The value text box is pushed to the bottom half of the control bounds to leave space for the title label. */
	layout.textBoxBounds.setTop(localBounds.getHeight() * 0.5f);

	return layout;
}

void IndentedWheelSlider_LookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
	using namespace Constants::IndentedRotarySliderTextBox;

	Rectangle<int> localBounds = slider.getLocalBounds();

	side = jmin(localBounds.getHeight(), localBounds.getWidth());
	halfSide = side * 0.5;
	rotaryKnobBounds = Rectangle<int>(localBounds.getCentreX() - halfSide, localBounds.getCentreY() - halfSide, side, side);
	localBounds.setBottom(localBounds.getHeight() * 0.5f);
	auto titleLabelBounds = localBounds;
	outerBevelBounds = rotaryKnobBounds.reduced(MARGIN_THICKNESS);		// Should be set in Constants.h
	indicatorBounds = rotaryKnobBounds.reduced(OUTER_BEVEL_THICKNESS);	// Should be set in Constants.h
	innerBevelBounds = indicatorBounds.reduced(INDICATOR_THICKNESS);	// Should be set in Constants.h

	/** Create the colour gradients if they don't exist. */
	if (!colourGradientsInitialized) makeGradients();

	/** Draw the outer bevel */
	g.setGradientFill(normalGradient);
	Path outerBevelPath;
	outerBevelPath.setUsingNonZeroWinding(false);
	outerBevelPath.addEllipse(outerBevelBounds.toFloat());
	outerBevelPath.addEllipse(indicatorBounds.toFloat());
	g.fillPath(outerBevelPath);

	/** Draw the indicator */
	valueIndicator.draw(g, indicatorBounds, sliderPosProportional, rotaryStartAngle, rotaryEndAngle, slider);
	

	/** Draw the inner bevel */
	g.setGradientFill(reverseGradient);
	Path innerBevelPath;
	innerBevelPath.setUsingNonZeroWinding(false);
	innerBevelPath.addEllipse(innerBevelBounds.toFloat());
	innerBevelPath.addEllipse(innerBevelBounds.reduced(10).toFloat());
	g.fillPath(innerBevelPath);

	

	/** Draw inner circle */
	g.setGradientFill(normalGradient);
	g.fillEllipse(innerBevelBounds.reduced(10).toFloat());

	/** Draw title label */
	g.setColour(Colours::grey);
	g.drawText(titleText, titleLabelBounds, Justification::centredBottom);
}

Label* IndentedWheelSlider_LookAndFeel::createSliderTextBox(Slider& slider)
{
	Label* sliderTextBoxPtr = LookAndFeel_V4::createSliderTextBox(slider);

	sliderTextBoxPtr->setColour(juce::Label::textColourId, juce::Colours::grey);
	sliderTextBoxPtr->setColour(juce::Label::backgroundColourId, juce::Colours::transparentBlack);
	sliderTextBoxPtr->setColour(juce::Label::outlineColourId, juce::Colours::transparentBlack);
	sliderTextBoxPtr->setColour(juce::Label::textWhenEditingColourId, juce::Colours::grey);
	sliderTextBoxPtr->setColour(juce::Label::backgroundWhenEditingColourId, juce::Colours::black);
	sliderTextBoxPtr->setColour(juce::Label::outlineWhenEditingColourId, juce::Colours::beige);

	/**
	 * This stops the user from being able to set a value directly,
	 * but also allows user to use the control through the slider textbox area.
	 */
	sliderTextBoxPtr->setInterceptsMouseClicks(false, true);

	return sliderTextBoxPtr;
}

void IndentedWheelSlider_LookAndFeel::makeGradients()
{
	normalGradient = ColourGradient(Colours::beige.darker(0.95), rotaryKnobBounds.getTopRight().toFloat(), Colours::beige, rotaryKnobBounds.getBottomLeft().toFloat(), false);
	reverseGradient = ColourGradient(Colours::beige, rotaryKnobBounds.getTopRight().toFloat(), Colours::beige.darker(0.95), rotaryKnobBounds.getBottomLeft().toFloat(), false);
	/** Raise the flag to indicate colour gradients are initialized. */
	colourGradientsInitialized = true;
}
