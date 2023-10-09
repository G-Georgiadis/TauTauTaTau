#include "NoteDurationDropDown.h"
#include <array>
NoteDurationDropDown::NoteDurationDropDown()
{
	/** Add the items to the menu */
	int i = 1;
	for (const juce::String nd :Constants::DropDownMenus::NOTE_DURATIONS)
	{
		this->addItem(nd, i);
		i++;
	}
	/** Set justification type */
	this->setJustificationType(Justification::centredLeft);

	/** Set LookAndFeel */
	this->setLookAndFeel(&noteDurationDropDown_LookAndFeel);
}

NoteDurationDropDown::~NoteDurationDropDown()
{
	this->setLookAndFeel(nullptr);
}