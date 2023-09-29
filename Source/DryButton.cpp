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
