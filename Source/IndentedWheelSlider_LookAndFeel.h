#pragma once
#include "JuceHeader.h"
#include "ValueIndicator.h"

using namespace juce;

class IndentedWheelSlider_LookAndFeel : public LookAndFeel_V4
{
public:
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
	int side;
	int halfSide;

	Rectangle<int> rotaryKnobBounds;
	Rectangle<int> outerBevelBounds;
	Rectangle<int> indicatorBounds;
	Rectangle<int> innerBevelBounds;


	ColourGradient normalGradient, reverseGradient;
	bool colourGradientsInitialized;
	void makeGradients();

	/** The arc that indicates the value */
	ValueIndicator valueIndicator;

	/** The text above the value indicating what this slider controls */
	const String titleText;

	static constexpr int numberOfDecimalPlaces = 2;
	static constexpr int marginThickness = 4;
	static constexpr int outerBevelThickness = 15;
	static constexpr int indicatorThickness = 4;
};