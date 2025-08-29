/*
  ==============================================================================

    GrooveListBox.h
    Created: 15 Jul 2025 10:55:58am
    Author:  evan

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

using namespace juce;

#define GROOVE_LISTBOX_HEIGHT 200
#define GROOVE_LISTBOX_WIDTH 250

class GrooveListBox : public ListBoxModel, public Component
{
    const int rowHeight{ 20 };
    int numRows{ 0 };

public:
    GrooveListBox();
    ~GrooveListBox();

    void clear();
    void updateContent();

    void add(String);

    void paint(Graphics& g) override;
    void resized() override;
    int  getNumRows() override;
    void paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) override;
    void selectedRowsChanged(int /*lastRowselected*/) override;

private:
    ListBox mListBox;
    StringArray mItems;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GrooveListBox)
};
