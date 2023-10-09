/*****************************************************************//**
 * \file   DryButton.h
 * \brief  Definitions for the DryButton.
 * 
 * \author George Georgiadis
 * \date   October 2023
 *********************************************************************/

#pragma once
#include "JuceHeader.h"

using namespace juce;

/** A simple toggle button used to enable or disable mixing the dry signal to the output. */
class DryButton : public TextButton
{
public:
	/** Initializes the DryButton. */
	DryButton();

	/** Draws the DryButton. */
	void paintButton(Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
private:
	/** The button state [On-Off] */
	bool state;
	/** Toggles the button state */
	void clicked() override;
};
