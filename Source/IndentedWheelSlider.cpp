#include "IndentedWheelSlider.h"

IndentedWheelSlider::IndentedWheelSlider(const String titleText) : indentedWheelSlider_LookAndFeel(titleText)
{
    setLookAndFeel(&indentedWheelSlider_LookAndFeel);

    setSliderStyle(Slider::RotaryVerticalDrag);

    setNumDecimalPlacesToDisplay(2);
}

IndentedWheelSlider::~IndentedWheelSlider()
{
    this->setLookAndFeel(nullptr);
}
