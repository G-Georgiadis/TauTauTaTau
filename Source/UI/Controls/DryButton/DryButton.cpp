/*****************************************************************//**
 * \file   DryButton.cpp
 * \brief  A 2-state button to control if the output should include the dry(without effect) signal.
 * \note	Comments are in the header file, or hover mouse over keyword if your IDE supports it.
 * 
 * \author George Georgiadis
 * \date   October 2023
 *********************************************************************/
#include "DryButton.h"

DryButton::DryButton() : state(false)
{
	setToggleable(true);
	setClickingTogglesState(true);
}

void DryButton::paintButton(Graphics& g, bool shouldDrawButtonAsHighlighted, bool )
{
	if (state)	//Pressed state
	{
		g.setColour(Colours::darkorange);
		g.fillRoundedRectangle(getLocalBounds().toFloat(), 5);

		g.setColour(Colours::grey);
		g.drawText("Dry", getLocalBounds().toFloat(), Justification::centred);
	}
	else		// Not pressed state
	{
		g.setColour(Colours::whitesmoke);
		g.fillRoundedRectangle(getLocalBounds().toFloat(), 5);

		g.setColour(Colours::grey);
		g.drawText("Dry", getLocalBounds().toFloat(), Justification::centred);
	}
	/** Draws a border when mouseover. */
	if (shouldDrawButtonAsHighlighted)
	{
		g.setColour(Colours::yellow);
		g.drawRoundedRectangle(getLocalBounds().toFloat(), 5, 1);
	}
}

void DryButton::clicked()
{
	state = !state;
}
