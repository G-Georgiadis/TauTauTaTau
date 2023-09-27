#pragma once
#include "JuceHeader.h"
#include "IndentedWheelSlider_LookAndFeel.h"

using namespace juce;

class IndentedWheelSlider : public Slider
{
public:
	IndentedWheelSlider(const String titleText);
	~IndentedWheelSlider();


private:
	IndentedWheelSlider_LookAndFeel indentedWheelSlider_LookAndFeel;
};
