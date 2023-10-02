#pragma once
#include "JuceHeader.h"

using namespace juce;

class MidiSyncSwitch : public ToggleButton
{
public:
	MidiSyncSwitch();

	void paintButton(Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
private:
	///** The button state [On-Off] */
	//bool state;
	///** Toggles the button state */
	//void clicked() override;
};
