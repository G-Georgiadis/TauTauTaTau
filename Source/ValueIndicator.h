/*****************************************************************//**
 * \file   ValueIndicator.h
 * \brief  A simple arc used to display the value selected in the IndentedWheelSlider
 * 
 * \author George Georgiadis
 * \date   October 2023
 *********************************************************************/

#pragma once
#include "JuceHeader.h"

using namespace juce;
/**
 * A simple arc used to display the value selected in the IndentedWheelSlider.
 * Implemented as a separate component to help with the Glow Effect (not yet implemented).
 */
class ValueIndicator : public Component
{
public:
	ValueIndicator() {};
	/** Draws the value indicator. */
	void draw(Graphics& g, Rectangle<int> bounds, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider& slider);
private:
};
