#include "MidiSyncSwitch.h"

MidiSyncSwitch::MidiSyncSwitch() : state(true), colourGradientsInitialized(false)
{
	this->onClick = [&]() { state = !state; };
}

void MidiSyncSwitch::paintButton(Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	if (!colourGradientsInitialized) makeGradients();

	auto localBounds = getLocalBounds();
	auto topBounds = Rectangle<float>(localBounds.getX(), localBounds.getY(), localBounds.getWidth(), localBounds.getHeight() / 2);
	//auto topBounds = localBounds.removeFromTop(localBounds.getHeight() / 2).toFloat();
	auto bottomBounds = Rectangle<float>(localBounds.getX(), localBounds.getHeight() / 2, localBounds.getWidth(), localBounds.getHeight() / 2);

	constexpr int cornerRadius = 5;

	/** Draw the background */
	g.setColour(Colours::grey);
	g.fillRoundedRectangle(localBounds.toFloat(), cornerRadius);

	if (!state)	// Draw the button off state
	{
		/** Background */
		g.setColour(Colours::lightgrey);
		g.fillRoundedRectangle(localBounds.toFloat(), cornerRadius);

		/** Button cap */
		g.setGradientFill(reverseGradient);
		g.fillRoundedRectangle(bottomBounds, cornerRadius);

		/** Text */
		g.setColour(Colours::grey);
		g.drawFittedText("Sec", topBounds.toNearestInt(), Justification::centred, 1);
	}
	else	//Draw the button on state
	{
		/** Background */
		g.setColour(Colours::darkorange);
		g.fillRoundedRectangle(localBounds.toFloat(), cornerRadius);

		/** Button cap */
		g.setGradientFill(reverseGradient);
		g.fillRoundedRectangle(topBounds, cornerRadius);
		
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