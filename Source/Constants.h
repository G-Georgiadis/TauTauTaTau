/*****************************************************************//**
 * \file   Constants.h
 * \brief  Contains all the constants used in the plugin.
 * 
 * \author George Georgiadis
 * \date   October 2023
 *********************************************************************/

#pragma once
#include "JuceHeader.h"


/**
 * Namespace that holds all the constants used in the TauTauTaTau cross deelay.
 */
namespace Constants
{
	/** Namespace that holds all the constants used in the IndentedRotarySliderTextBoxes */
	namespace IndentedRotarySliderTextBox
	{
		/** The number of decimal digits used in rotary slider textboxes. */
		static constexpr int NUMBER_OF_DECIMAL_DIGITS = 2;
		/** The thickness of the margin between the rotary knob outer bounds and the outer beve. Used to that controls that are next to each other do not touch. */
		static constexpr int MARGIN_THICKNESS = 4;
		/** The thickness of the rotary knob outer bevel. */
		static constexpr int OUTER_BEVEL_THICKNESS = 15;
		/** The thickness of the rotary knob value indicator */
		static constexpr int INDICATOR_THICKNESS = 4;
	}

	namespace DropDownMenus
	{

		static constexpr int DROP_DOWN_MENU_HEIGHT = 20;

		static const juce::StringArray NOTE_DURATIONS =
		{
			"8 Bars",
			"6 Bars",
			"5 Bars",
			"4 Bars",
			"3 Bars",
			"2 Bars",
			"1 Bar",
			"1/2d",
			"1/2",
			"1/2t",
			"1/4d",
			"1/4",
			"1/4t",
			"1/8d",
			"1/8",
			"1/8t",
			"1/16d",
			"1/16",
			"1/16t",
			"1/32d",
			"1/32",
			"1/32t",
			"1/64d",
			"1/64",
			"1/64t"
		};
	}

	/** Namespace that holds all the constants used in the MidiSyncSwitch. */
	namespace MidiSyncSwitch
	{
		constexpr int CORNER_RADIUS = 5;
	}

	namespace DSP
	{
		static constexpr float MAXIMUM_DELAY_IN_SAMPLES = 30.f;
	}
}
