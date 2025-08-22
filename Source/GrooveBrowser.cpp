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
}

GrooveBrowser::~GrooveBrowser() {
}

void GrooveBrowser::Initialize(File f) {
    lists.clear();

    store.Initialize(f);

    auto maxDepth(store.MaxDepth());

    for (int i = 0; i < maxDepth + 1; i++)
        lists.add(std::make_unique<GrooveList>());

    store.Enumerate([&](const GrooveFolder& gf) {
        std::string indentation("");
        for (int i = 0; i < gf.level; i++)
            indentation += "  ";

        if (gf.level == 1) {
            MYDBG(indentation + gf.folder);
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
