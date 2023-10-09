#pragma once
#include "JuceHeader.h"
#include "..\..\..\Constants.h"


using namespace juce;

class NoteDurationDropDown_LookAndFeel : public LookAndFeel_V4
{
	void drawComboBox(Graphics& g, int width, int height, bool,
		int, int, int, int, ComboBox& box)
	{
		Rectangle<int> boxBounds(0, 0, width, height);

		/** Background */
		g.setColour(Colours::whitesmoke);
		g.fillRoundedRectangle(boxBounds.toFloat(), Constants::MidiSyncSwitch::CORNER_RADIUS);

		g.setColour(Colours::lightgrey);
		g.drawRoundedRectangle(boxBounds.toFloat().reduced(0.5f, 0.5f), Constants::MidiSyncSwitch::CORNER_RADIUS, 1.0f);

		/** Arrow path */
		Rectangle<int> arrowZone(width - 30, 0, 20, height);
		Path path;
		path.startNewSubPath((float)arrowZone.getX() + 3.0f, (float)arrowZone.getCentreY() - 2.0f);
		path.lineTo((float)arrowZone.getCentreX(), (float)arrowZone.getCentreY() + 3.0f);
		path.lineTo((float)arrowZone.getRight() - 3.0f, (float)arrowZone.getCentreY() - 2.0f);

		/** Draw arrow */
		g.setColour(Colours::darkorange);
		g.strokePath(path, PathStrokeType(2.0f));
	}

	Font getComboBoxFont(ComboBox& box)
	{
		return { jmin(16.0f, (float)box.getHeight() * 0.85f) };
	}

	Label* createComboBoxTextBox(ComboBox&)
	{
		return new Label(String(), String());
	}

	void positionComboBoxText(ComboBox& box, Label& label)
	{
		label.setBounds(1, 1,
			box.getWidth() - 30,
			box.getHeight() - 2);

		label.setFont(getComboBoxFont(box));
		/** Set text colour */
		label.setColour(Label::ColourIds::textColourId, Colours::grey);
	}

	PopupMenu::Options getOptionsForComboBoxPopupMenu(ComboBox& box, Label& label)
	{
		return PopupMenu::Options().withTargetComponent(&box)
			.withItemThatMustBeVisible(box.getSelectedId())
			.withInitiallySelectedItem(box.getSelectedId())
			.withMinimumWidth(box.getWidth())
			.withMaximumNumColumns(1)
			.withStandardItemHeight(label.getHeight());

	}

	void drawPopupMenuItem(Graphics& g,
		const Rectangle< int >& area,
		bool  	isSeparator,
		bool  	isActive,
		bool  	isHighlighted,
		bool  	isTicked,
		bool  	hasSubMenu,
		const String& text,
		const String& shortcutKeyText,
		const Drawable* icon,
		const Colour* textColourToUse
	) override
	{
		if (isSeparator)
		{
			auto r = area.reduced(5, 0);
			r.removeFromTop(roundToInt(((float)r.getHeight() * 0.5f) - 0.5f));

			g.setColour(findColour(PopupMenu::textColourId).withAlpha(0.3f));
			g.fillRect(r.removeFromTop(1));
		}
		else
		{
			auto textColour = (textColourToUse == nullptr ? findColour(PopupMenu::textColourId)
				: *textColourToUse);

			auto r = area.reduced(1);

			if (isHighlighted && isActive)
			{
				g.setColour(findColour(PopupMenu::highlightedBackgroundColourId));
				g.fillRect(r);

				g.setColour(findColour(PopupMenu::highlightedTextColourId));
			}
			else
			{
				g.setColour(textColour.withMultipliedAlpha(isActive ? 1.0f : 0.5f));
			}

			r.reduce(jmin(5, area.getWidth() / 20), 0);

			auto font = getPopupMenuFont();

			auto maxFontHeight = (float)r.getHeight() / 1.3f;

			if (font.getHeight() > maxFontHeight)
				font.setHeight(maxFontHeight);

			g.setFont(font);

			auto iconArea = r.removeFromLeft(roundToInt(maxFontHeight)).toFloat();

			if (icon != nullptr)
			{
				icon->drawWithin(g, iconArea, RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.0f);
				r.removeFromLeft(roundToInt(maxFontHeight * 0.5f));
			}
			else if (isTicked)
			{
				auto tick = getTickShape(1.0f);
				g.fillPath(tick, tick.getTransformToScaleToFit(iconArea.reduced(iconArea.getWidth() / 5, 0).toFloat(), true));
			}

			if (hasSubMenu)
			{
				auto arrowH = 0.6f * getPopupMenuFont().getAscent();

				auto x = static_cast<float> (r.removeFromRight((int)arrowH).getX());
				auto halfH = static_cast<float> (r.getCentreY());

				Path path;
				path.startNewSubPath(x, halfH - arrowH * 0.5f);
				path.lineTo(x + arrowH * 0.6f, halfH);
				path.lineTo(x, halfH + arrowH * 0.5f);

				g.strokePath(path, PathStrokeType(2.0f));
			}

			r.removeFromRight(3);
			g.drawFittedText(text, r, Justification::centredLeft, 1);

			if (shortcutKeyText.isNotEmpty())
			{
				auto f2 = font;
				f2.setHeight(f2.getHeight() * 0.75f);
				f2.setHorizontalScale(0.95f);
				g.setFont(f2);

				g.drawText(shortcutKeyText, r, Justification::centredRight, true);
			}
		}
	}

	void drawPopupMenuBackground(
		Graphics& g,
		int  	width,
		int  	height
	) override
	{
		/** PopupMenu background */
		g.setColour(Colours::lightgrey);
		g.fillAll();
	}

	void drawComboBoxTextWhenNothingSelected(Graphics& g, ComboBox& box, Label& label)
	{
		g.setColour(findColour(ComboBox::textColourId).withMultipliedAlpha(0.5f));

		auto font = label.getLookAndFeel().getLabelFont(label);

		g.setFont(font);

		auto textArea = getLabelBorderSize(label).subtractedFrom(label.getLocalBounds());

		g.drawFittedText(box.getTextWhenNothingSelected(), textArea, label.getJustificationType(),
			jmax(1, (int)((float)textArea.getHeight() / font.getHeight())),
			label.getMinimumHorizontalScale());
	}
};
