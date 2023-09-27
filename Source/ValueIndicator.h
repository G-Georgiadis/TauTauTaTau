#pragma once
#include "JuceHeader.h"

using namespace juce;

class ValueIndicator : public Component
{
public:
	ValueIndicator();
	void draw(Graphics& g, Rectangle<int> bounds, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider& slider);
private:
	GlowEffect glow;
};
