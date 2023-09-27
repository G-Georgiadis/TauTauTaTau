#include "IndentedWheelSlider_LookAndFeel.h"

IndentedWheelSlider_LookAndFeel::IndentedWheelSlider_LookAndFeel(const String newTitleText)
	: side(0),
	halfSide(0),
	normalGradient(),
	reverseGradient(),
	colourGradientsInitialized(false),
	valueIndicator(),
	titleText(newTitleText)
{
	
}

IndentedWheelSlider_LookAndFeel::~IndentedWheelSlider_LookAndFeel()
{
}

Slider::SliderLayout IndentedWheelSlider_LookAndFeel::getSliderLayout(Slider& slider)
{
	Slider::SliderLayout layout;

	Rectangle<int> localBounds = slider.getLocalBounds();
	layout.sliderBounds = localBounds;
	layout.textBoxBounds = localBounds.reduced(0.35 * localBounds.getWidth(), 0.4f * localBounds.getHeight());
	layout.textBoxBounds.setTop(localBounds.getHeight() * 0.5f);
	return layout;
}

void IndentedWheelSlider_LookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
	Rectangle<int> localBounds = slider.getLocalBounds();

	side = jmin(localBounds.getHeight(), localBounds.getWidth());
	halfSide = side * 0.5;
	rotaryKnobBounds = Rectangle<int>(localBounds.getCentreX() - halfSide, localBounds.getCentreY() - halfSide, side, side);
	localBounds.setBottom(localBounds.getHeight() * 0.5f);
	auto titleLabelBounds = localBounds;
	outerBevelBounds = rotaryKnobBounds.reduced(marginThickness);
	indicatorBounds = rotaryKnobBounds.reduced(outerBevelThickness);
	innerBevelBounds = indicatorBounds.reduced(indicatorThickness);

	if (!colourGradientsInitialized) makeGradients();

	/** Draw the outer bevel */
	g.setGradientFill(normalGradient);
	Path outerBevelPath;
	outerBevelPath.setUsingNonZeroWinding(false);
	outerBevelPath.addEllipse(outerBevelBounds.toFloat());
	outerBevelPath.addEllipse(indicatorBounds.toFloat());
	g.fillPath(outerBevelPath);

	/** Draw the indicator */
	valueIndicator.draw(g, indicatorBounds, sliderPosProportional, rotaryStartAngle, rotaryEndAngle, slider);
	

	/** Draw the inner bevel */
	g.setGradientFill(reverseGradient);
	Path innerBevelPath;
	innerBevelPath.setUsingNonZeroWinding(false);
	innerBevelPath.addEllipse(innerBevelBounds.toFloat());
	innerBevelPath.addEllipse(innerBevelBounds.reduced(10).toFloat());
	g.fillPath(innerBevelPath);

	

	/** Draw inner circle */
	g.setGradientFill(normalGradient);
	g.fillEllipse(innerBevelBounds.reduced(10).toFloat());

	/** Draw title label */
	g.setColour(Colours::grey);
	g.drawText(titleText, titleLabelBounds, Justification::centredBottom);
}

Label* IndentedWheelSlider_LookAndFeel::createSliderTextBox(Slider& slider)
{
	Label* sliderTextBoxPtr = LookAndFeel_V4::createSliderTextBox(slider);

	sliderTextBoxPtr->setColour(juce::Label::textColourId, juce::Colours::grey);
	sliderTextBoxPtr->setColour(juce::Label::backgroundColourId, juce::Colours::transparentBlack);
	sliderTextBoxPtr->setColour(juce::Label::outlineColourId, juce::Colours::transparentBlack);
	sliderTextBoxPtr->setColour(juce::Label::textWhenEditingColourId, juce::Colours::grey);
	sliderTextBoxPtr->setColour(juce::Label::backgroundWhenEditingColourId, juce::Colours::black);
	sliderTextBoxPtr->setColour(juce::Label::outlineWhenEditingColourId, juce::Colours::beige);

	sliderTextBoxPtr->setInterceptsMouseClicks(false, true);

	return sliderTextBoxPtr;
}

void IndentedWheelSlider_LookAndFeel::makeGradients()
{
	normalGradient = ColourGradient(Colours::whitesmoke.darker(0.2), rotaryKnobBounds.getTopRight().toFloat(), Colours::whitesmoke, rotaryKnobBounds.getBottomLeft().toFloat(), false);
	reverseGradient = ColourGradient(Colours::whitesmoke, rotaryKnobBounds.getTopRight().toFloat(), Colours::whitesmoke.darker(0.2), rotaryKnobBounds.getBottomLeft().toFloat(), false);
	colourGradientsInitialized = true;
}
