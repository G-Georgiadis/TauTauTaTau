#pragma once
#include "JuceHeader.h"

using namespace juce;

class MidiSyncSwitch : public ToggleButton
{
public:
	MidiSyncSwitch();
	/** Draws the button */
	void paintButton(Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
private:
	/** The button state [On-Off] */
	bool state;
	bool colourGradientsInitialized;
	ColourGradient normalGradient;
	ColourGradient reverseGradient;

	void makeGradients();
};
