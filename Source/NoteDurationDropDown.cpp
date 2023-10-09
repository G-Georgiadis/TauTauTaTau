#include "NoteDurationDropDown.h"
#include <array>
NoteDurationDropDown::NoteDurationDropDown()
{
	int i = 1;
	for (const juce::String nd :Constants::DropDownMenus::NOTE_DURATIONS)
	{
		this->addItem(nd, i);
		i++;
	}
}

NoteDurationDropDown::~NoteDurationDropDown()
{
}