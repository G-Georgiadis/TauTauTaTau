

#pragma once
#include "JuceHeader.h"
#include "..\..\..\Constants.h"
#include "NoteDurationDropDown_LookAndFeel.h"

using namespace juce;

class NoteDurationDropDown : public ComboBox
{
public:
	NoteDurationDropDown();
	~NoteDurationDropDown();

private:
	NoteDurationDropDown_LookAndFeel noteDurationDropDown_LookAndFeel;
};

