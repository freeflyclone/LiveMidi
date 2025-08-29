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
    addAndMakeVisible(mListBox);
    mListBox.setRowHeight(rowHeight);
    mListBox.setModel(this);   // Tell the listbox where to get its data model

    mListBox.setColour(ListBox::textColourId, Colours::ghostwhite);
    mListBox.setColour(ListBox::backgroundColourId, Colour(0xFF1F1F1F));
    mListBox.setColour(ListBox::outlineColourId, Colour(0xFF606060));
    mListBox.setOutlineThickness(1);

    ScrollBar& vScroll = mListBox.getVerticalScrollBar();
    vScroll.setVisible(true);
    vScroll.getLookAndFeel().setColour(ScrollBar::thumbColourId, Colour(0xFF3f3f3f));

    setSize(GROOVE_LISTBOX_WIDTH, GROOVE_LISTBOX_HEIGHT);
}

GrooveListBox::~GrooveListBox() {
}

void GrooveListBox::clear() {
    mItems.clear();
}

void GrooveListBox::updateContent() {
    mListBox.updateContent();
}

void GrooveListBox::add(String item) {
    mItems.add(item);
}

void GrooveListBox::paint(Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void GrooveListBox::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    mListBox.setBounds(0, 0, GROOVE_LISTBOX_WIDTH, GROOVE_LISTBOX_HEIGHT);
}

// The following methods implement the ListBoxModel virtual methods:
int GrooveListBox::getNumRows()
{
    return mItems.size();
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

    g.drawText(mItems[rowNumber], 5, 0, width, height, Justification::centredLeft, true);
}

void GrooveListBox::selectedRowsChanged(int lastRowSelected)
{
    //do stuff when selection changes
    sendActionMessage( getComponentID() + "::selectedRowsChanged " + mItems[lastRowSelected]);
}

