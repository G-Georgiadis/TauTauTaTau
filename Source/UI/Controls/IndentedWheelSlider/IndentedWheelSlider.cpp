/*****************************************************************//**
 * \file   IndentedWheelSlider.cpp
 * \brief  An indented rotary slider.
 * \note	Comments are in the header file, or hover mouse over keyword if your IDE supports it.
 * 
 * \author George Georgiadis
 * \date   October 2023
 *********************************************************************/

#include "IndentedWheelSlider.h"

IndentedWheelSlider::IndentedWheelSlider(const String titleText) : indentedWheelSlider_LookAndFeel(titleText)
{
    this->setLookAndFeel(&indentedWheelSlider_LookAndFeel);

    this->setSliderStyle(Slider::RotaryVerticalDrag);

    /** The value should be set in Constants.h */
    this->setNumDecimalPlacesToDisplay(Constants::IndentedRotarySliderTextBox::NUMBER_OF_DECIMAL_DIGITS);
}

IndentedWheelSlider::~IndentedWheelSlider()
{
    this->setLookAndFeel(nullptr);
}
