/*****************************************************************//**
 * \file   IndentedWheelSlider_LookAndFeel.h
 * \brief  Definitions for the IndentedWheelSlider_LookAndFeel.
 * 
 * \author George Georgiadis
 * \date   October 2023
 *********************************************************************/

#pragma once
#include "JuceHeader.h"
#include "ValueIndicator.h"
#include "Constants.h"

using namespace juce;

/**
 * An indented rotary slider.
 */
class IndentedWheelSlider_LookAndFeel : public LookAndFeel_V4
{
public:
	/**
	 * Initialized the IndentedWheelSlider_LookAndFeel.
	 * 
	 * \param titleText	The text to use as the control title.
	 */
	IndentedWheelSlider_LookAndFeel(const String titleText);

	/**
	 * Defines the bounds for the slider and the text box.
	 *
	 * \param slider A slider. Used to access it's bounds and derive the slider and text box areas.
	 * \return A Slider::SliderLayout
	 */
	Slider::SliderLayout getSliderLayout(Slider& slider) override;

	/**
	 * Draws the rotary slider.
	 */
	void drawRotarySlider(
		Graphics& g,
		int x,
		int y,
		int width,
		int height,
		float sliderPosProportional,
		float rotaryStartAngle,
		float rotaryEndAngle,
		Slider& slider
	) override;

	/** Draws the text box of the rotary knob. */
	Label* createSliderTextBox(Slider& slider) override;
private:
	/** The smallest of Width and Height since we want a square.  */
	int side;
	/** Side / 2 pre-calculated */
	int halfSide;
	/** The bounds of the rotary knob */
	Rectangle<int> rotaryKnobBounds;
	/** Bounds of the outer bevel */
	Rectangle<int> outerBevelBounds;
	/** Bounds of the value indicator */
	Rectangle<int> indicatorBounds;
	/** Bounds of the inner bevel */
	Rectangle<int> innerBevelBounds;

	/** Shading gradient (top side dark) */
	ColourGradient normalGradient;
	/** Shading gradient (bottom side dark) */
	ColourGradient reverseGradient;
	/**
	 * Flag that indicates if the colour gradients have been initialized.
	 * Used to run makeGradients only once.
	 */
	bool colourGradientsInitialized;
	/**
	 * Generates the colour gradients. It uses getLocalBounds(), so it MUST be called
	 * after the calling component has had it's bounds set (not in the constructor).
	 */
	void makeGradients();

	/** The arc that indicates the value */
	ValueIndicator valueIndicator;

	/** The text above the value indicating what this slider controls */
	const String titleText;
};