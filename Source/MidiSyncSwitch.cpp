#include "MidiSyncSwitch.h"

MidiSyncSwitch::MidiSyncSwitch()
{
	this->setToggleState(true, sendNotification);
}

void MidiSyncSwitch::paintButton(Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	if (this->getState() == buttonNormal)	// Draw the button off state
	{
		g.fillAll(Colours::red);
	}
	else	//Draw the button on state
	{
		g.fillAll(Colours::green);
	}
}
