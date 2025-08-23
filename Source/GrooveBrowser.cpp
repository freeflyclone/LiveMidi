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
}

GrooveBrowser::~GrooveBrowser() {
}

void GrooveBrowser::Initialize(File f) {
    store.Initialize(f);

    auto maxDepth(store.MaxDepth());

    store.Enumerate([&](const GrooveFolder& gf) {
        std::string indentation("");
        for (int i = 0; i < gf.level; i++)
            indentation += "  ";

        if (gf.level == 1) {
            lists[0].add(gf.folder);
            MYDBG(indentation + gf.folder.toStdString());
        }
    });

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
