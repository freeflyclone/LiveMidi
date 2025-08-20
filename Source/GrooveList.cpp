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

#define LISTHEIGHT (rowHeight * numRows * 2 / 3)
#define LISTWIDTH 200

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

GrooveList::~GrooveList()
{
    MYDBG(__FUNCTION__);
}

void GrooveList::fetchGroovesFromFolder(String name)
{
    auto f = File(name);

    Array<File> groovesList = f.findChildFiles(File::findFiles, false, "*.mid");
    StringArray grooves;

    for (const auto& groove : groovesList) {
        grooves.add(groove.getRelativePathFrom(f));
    }

    MYDBG("Found " + std::to_string(groovesList.size()) + " grooves");

    for (const auto& g : grooves)
        MYDBG("groove: " + g.toStdString());
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
    return numRows; //you should probably derive this from whatever source data you end up using
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

    g.drawText("Row Number " + String(rowNumber + 1), 5, 0, width, height, Justification::centredLeft, true);
}

void GrooveList::selectedRowsChanged(int lastRowselected)
{
    //do stuff when selection changes
    MYDBG("Row Selected: " + std::to_string(lastRowselected));
}

