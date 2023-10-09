/*****************************************************************//**
 * \file   MidiSyncSwitch.cpp
 * \brief  A 2-state switch made to control swicthing between Sec and Midi Sync.
 * \note	Comments are in the header file, or hover mouse over keyword if your IDE supports it.
 * 
 * \author George Georgiadis
 * \date   October 2023
 *********************************************************************/
#include "MidiSyncSwitch.h"
#include "..\..\..\Constants.h"

MidiSyncSwitch::MidiSyncSwitch() : state(false), colourGradientsInitialized(false)
{
	this->onClick = [&]() { state = !state; };	// Clicking toggles state
}

void MidiSyncSwitch::paintButton(Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	if (!colourGradientsInitialized) makeGradients();

	auto localBounds = getLocalBounds();
	auto topBounds = Rectangle<float>(localBounds.getX(), localBounds.getY(), localBounds.getWidth(), localBounds.getHeight() / 2);
	auto bottomBounds = Rectangle<float>(localBounds.getX(), localBounds.getHeight() / 2, localBounds.getWidth(), localBounds.getHeight() / 2);

	using namespace Constants::MidiSyncSwitch;

	/** Draw the background */
	g.setColour(Colours::grey);
	g.fillRoundedRectangle(localBounds.toFloat(), CORNER_RADIUS);	// The corner radius can be set in Constants.h

	if (!state)	// Draw the button off state
	{
		/** Background */
		g.setColour(Colours::lightgrey);
		g.fillRoundedRectangle(localBounds.toFloat(), CORNER_RADIUS);

		/** Button cap */
		g.setGradientFill(reverseGradient);
		g.fillRoundedRectangle(bottomBounds, CORNER_RADIUS);

		/** Text */
		g.setColour(Colours::grey);
		g.drawFittedText("Sec", topBounds.toNearestInt(), Justification::centred, 1);
	}
	else	//Draw the button on state
	{
		/** Background */
		g.setColour(Colours::darkorange);
		g.fillRoundedRectangle(localBounds.toFloat(), CORNER_RADIUS);

		/** Button cap */
		g.setGradientFill(reverseGradient);
		g.fillRoundedRectangle(topBounds, CORNER_RADIUS);
		
		/** Text */
		g.setColour(Colours::grey);		
		g.drawFittedText("Sync", bottomBounds.toNearestInt(), Justification::centred, 1);
	}
}

void MidiSyncSwitch::makeGradients()
{
	auto localBounds = getLocalBounds();
	normalGradient = ColourGradient(Colours::whitesmoke.darker(0.95), localBounds.getTopRight().toFloat(), Colours::whitesmoke, localBounds.getBottomLeft().toFloat(), false);
	reverseGradient = ColourGradient(Colours::whitesmoke, localBounds.getTopRight().toFloat(), Colours::whitesmoke.darker(0.95), localBounds.getBottomLeft().toFloat(), false);
	/** Raise the flag to indicate colour gradients are initialized. */
	colourGradientsInitialized = true;
}