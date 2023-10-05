/*****************************************************************//**
 * \file   Constants.h
 * \brief  Contains all the constants used in the plugin.
 * 
 * \author George Georgiadis
 * \date   October 2023
 *********************************************************************/

#pragma once

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
