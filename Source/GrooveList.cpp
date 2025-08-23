/*
  ==============================================================================

    GrooveList.cpp
    Created: 15 Jul 2025 10:55:58am
    Author:  evan

  ==============================================================================
*/

#include "JuceHeader.h"
#include "Log.h"
#include "GrooveList.h"

#define LISTHEIGHT 200
#define LISTWIDTH 300

GrooveList::GrooveList()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(listBox);
    listBox.setRowHeight(rowHeight);
    listBox.setModel(this);   // Tell the listbox where to get its data model

    listBox.setColour(ListBox::textColourId, Colours::ghostwhite);
    listBox.setColour(ListBox::backgroundColourId, Colour(0xFF1F1F1F));
    listBox.setColour(ListBox::outlineColourId, Colour(0xFF606060));
    listBox.setOutlineThickness(1);

    ScrollBar& vScroll = listBox.getVerticalScrollBar();
    vScroll.setVisible(true);
    vScroll.getLookAndFeel().setColour(ScrollBar::thumbColourId, Colour(0xFF3f3f3f));

    setSize(LISTWIDTH, LISTHEIGHT);

    MYDBG(__FUNCTION__);
}

GrooveList::~GrooveList() {
    MYDBG(__FUNCTION__);
}

void GrooveList::clear() {
    items.clear();
}

void GrooveList::updateContent() {
    listBox.updateContent();
}

void GrooveList::add(String item) {
    items.add(item);
}

void GrooveList::paint(Graphics& g)
{
    MYDBG(__FUNCTION__);

    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void GrooveList::resized()
{
    MYDBG(__FUNCTION__);

    // This method is where you should set the bounds of any child
    // components that your component contains..
    listBox.setBounds(0, 0, LISTWIDTH, LISTHEIGHT);
}

// The following methods implement the ListBoxModel virtual methods:
int GrooveList::getNumRows()
{
    return items.size();
}

void GrooveList::paintListBoxItem(int rowNumber, Graphics& g,int width, int height, bool rowIsSelected)
{

    if (rowIsSelected)
    {
        g.fillAll(Colour(0xFFafafaf));
        g.setColour(Colours::black);
    }
    else {
        g.setColour(Colours::ghostwhite);
    }

    g.setFont(height * 0.85f);

    g.drawText(items[rowNumber], 5, 0, width, height, Justification::centredLeft, true);
}

void GrooveList::selectedRowsChanged(int lastRowselected)
{
    //do stuff when selection changes
    MYDBG("Row Selected: " + std::to_string(lastRowselected));
}

