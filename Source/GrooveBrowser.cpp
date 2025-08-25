/*
  ==============================================================================

    GrooveBrowser.cpp
    Created: 22 Aug 2025 10:37:17am
    Author:  evan

  ==============================================================================
*/

#include "GrooveBrowser.h"
#include "Log.h"

GrooveBrowser::GrooveBrowser()
{
    addAndMakeVisible(lists[0]);

    addAndMakeVisible(lists[1]);
    lists[1].setTopLeftPosition(GROOVE_LISTBOX_WIDTH-1, 0);

    addAndMakeVisible(lists[2]);
    lists[2].setTopLeftPosition((GROOVE_LISTBOX_WIDTH-1) * 2, 0);
}

GrooveBrowser::~GrooveBrowser() {
}

void GrooveBrowser::Initialize(File f) {
    store.Initialize(f);

    auto maxDepth(store.MaxDepth());

    lists[0].clear();

    store.Enumerate([&](const GrooveFolder& gf) {
    });

    lists[0].updateContent();

    repaint();
}

void GrooveBrowser::paint(Graphics& g) {
    if (store.MaxDepth())
        g.fillAll(Colour(0xff7f7f7f));
    else
        g.fillAll(Colour(0xff000000));
}

void GrooveBrowser::resized() {
    // Here's where we'll manage set of GrooveList children according to
    // GrooveStore::MaxDepth()
}
