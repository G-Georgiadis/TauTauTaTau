/*****************************************************************//**
 * \file   IndentedWheelSlider.h
 * \brief  Definitions for the IndentedWheelSlider.
 * 
 * \author George georgiadis
 * \date   October 2023
 *********************************************************************/

#pragma once
#include "JuceHeader.h"
#include "IndentedWheelSlider_LookAndFeel.h"

using namespace juce;

/**
 * Defines an indented rotary slider. This just sets the look and feel,
 * style and number of decimal places. All the look and feel
 * definitions are in IndentedWheelSlider_LookAndFeel.
 */
class IndentedWheelSlider : public Slider
{
public:
	/** Initializes the IndentedWheelSlider. */
	IndentedWheelSlider(const String titleText);
	/** Used to unset the LookAndFeel so that it can be destroyed. */
	~IndentedWheelSlider();
private:
	/** Defines the look and interaction of the IndentedWheelSlider_LookAndFeel. */
	IndentedWheelSlider_LookAndFeel indentedWheelSlider_LookAndFeel;
};
