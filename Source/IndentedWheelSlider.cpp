#include "IndentedWheelSlider.h"

IndentedWheelSlider::IndentedWheelSlider(const String titleText) : indentedWheelSlider_LookAndFeel(titleText)
{
    this->setLookAndFeel(&indentedWheelSlider_LookAndFeel);

    this->setSliderStyle(Slider::RotaryVerticalDrag);

    this->setNumDecimalPlacesToDisplay(2);
}

IndentedWheelSlider::~IndentedWheelSlider()
{
    this->setLookAndFeel(nullptr);
}
