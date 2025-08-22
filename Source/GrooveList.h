/*
  ==============================================================================

    GrooveList.h
    Created: 15 Jul 2025 10:55:58am
    Author:  evan

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

using namespace juce;

class GrooveList : public ListBoxModel, public Component
{
    const int rowHeight{ 20 };
    int numRows{ 12 };

public:
    GrooveList();
    ~GrooveList();

    void fetchGroovesFromFolder(String);
    void populate(std::vector<std::string>);

    void paint(Graphics& g) override;
    void resized() override;
    int  getNumRows() override;
    void paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) override;
    void selectedRowsChanged(int /*lastRowselected*/) override;

private:
    ListBox listBox;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GrooveList)
};