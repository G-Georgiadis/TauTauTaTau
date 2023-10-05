/*****************************************************************//**
 * \file   MidiSyncSwitch.h
 * \brief  Definitions for the MidiSyncSwitch.
 * 
 * \author George Georgiadis
 * \date   October 2023
 *********************************************************************/

#pragma once
#include "JuceHeader.h"

using namespace juce;

/**
 * A switch for dis/en-abling MIDI syncing. It has 2 states: Sec for setting delay time in Sec and Sync for setting time with note durations.
 */
class MidiSyncSwitch : public ToggleButton
{
public:
	/** Initializes the MidiSyncButton */
	MidiSyncSwitch();
	/** Draws the button. 1st it is called, it initializes the colour gradients. */
	void paintButton(Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
private:
	/** The button state [On-Off] */
	bool state;
	/** Flag indicating if the colour gradients used have been initialized. Used so that they are only calulated once. */
	bool colourGradientsInitialized;
	/** Shading gradient (top side dark) */
	ColourGradient normalGradient;
	/** Shading gradient (bottom side dark) */
	ColourGradient reverseGradient;
	/**
	 * Generates the colour gradients. It uses getLocalBounds(), so it MUST be called
	 * after the calling component has had it's bounds set (not in the constructor).
	 */
	void makeGradients();
};
