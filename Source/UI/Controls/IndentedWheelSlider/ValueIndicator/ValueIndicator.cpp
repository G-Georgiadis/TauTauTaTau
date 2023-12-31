/*****************************************************************//**
 * \file    ValueIndicator.cpp
 * \brief   A simple arc used to display the value selected in the IndentedWheelSlider
 * \note    Comments are in the header file, or hover mouse over keyword if your IDE supports it.
 * 
 * \author George Georgiadis
 * \date   October 2023
 *********************************************************************/

#include "ValueIndicator.h"
void ValueIndicator::draw(Graphics& g, Rectangle<int> bounds, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    float lineThickness = 4;

    bounds.reduce(lineThickness * 0.5, lineThickness * 0.5);

    const float x = bounds.getX();
    const float y = bounds.getY();
    const float width = bounds.getWidth();
    const float height = bounds.getHeight();
    auto side = (width < height) ? width : height;
    auto scaledEndAngle = jmap<float>(sliderPosProportional, 0.f, 1.f, rotaryStartAngle, rotaryEndAngle);
    
    g.setColour(Colours::grey);
    g.drawEllipse(bounds.toFloat(), lineThickness);

    Path valuePath;    
    valuePath.addArc(x, y, width, width, rotaryStartAngle, scaledEndAngle, true);
    
    g.setColour(Colours::darkorange); 
    g.strokePath(valuePath, PathStrokeType(3));
}
