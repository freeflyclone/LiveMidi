/*
  ==============================================================================

    GrooveList.cpp
    Created: 15 Jul 2025 10:55:58am
    Author:  evan

  ==============================================================================
*/

#include "JuceHeader.h"
#include "Log.h"
#include "GrooveListBox.h"

GrooveListBox::GrooveListBox()
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

    setSize(GROOVE_LISTBOX_WIDTH, GROOVE_LISTBOX_HEIGHT);
}

GrooveListBox::~GrooveListBox() {
}

void GrooveListBox::clear() {
    items.clear();
}

void GrooveListBox::updateContent() {
    listBox.updateContent();
}

void GrooveListBox::add(String item) {
    items.add(item);
}

void GrooveListBox::paint(Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void GrooveListBox::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    listBox.setBounds(0, 0, GROOVE_LISTBOX_WIDTH, GROOVE_LISTBOX_HEIGHT);
}

// The following methods implement the ListBoxModel virtual methods:
int GrooveListBox::getNumRows()
{
    return items.size();
}

void GrooveListBox::paintListBoxItem(int rowNumber, Graphics& g,int width, int height, bool rowIsSelected)
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

void GrooveListBox::selectedRowsChanged(int lastRowselected)
{
    //do stuff when selection changes
    MYDBG("Row Selected: " + std::to_string(lastRowselected));
}

