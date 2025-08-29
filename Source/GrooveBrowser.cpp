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
    addAndMakeVisible(mLists[0]);

    addAndMakeVisible(mLists[1]);
    mLists[1].setTopLeftPosition(GROOVE_LISTBOX_WIDTH-1, 0);

    addAndMakeVisible(mLists[2]);
    mLists[2].setTopLeftPosition((GROOVE_LISTBOX_WIDTH-1) * 2, 0);
}

GrooveBrowser::~GrooveBrowser() {
}

void GrooveBrowser::Initialize(File f) {
    mStore.Initialize(f);

    auto maxDepth(mStore.MaxDepth());

    mLists[0].clear();

    mStore.Enumerate([](GrooveFolder& gf) {
        auto& fileSelf = gf.GetSelfFile();

        MYDBG("enumerating: " + fileSelf.getFileName().toStdString());

        for (const auto child : gf.GetChildren()) {
            MYDBG("  " + child->GetSelfFile().getFileName().toStdString() + ", parent: " + child->GetParent()->GetSelfFile().getFileName().toStdString());
        }

        for (const auto fileName : gf.GetFileNames())
            MYDBG("    " + fileName.toStdString());
    });

    mLists[0].updateContent();

    repaint();
}

void GrooveBrowser::paint(Graphics& g) {
    if (mStore.MaxDepth())
        g.fillAll(Colour(0xff7f7f7f));
    else
        g.fillAll(Colour(0xff000000));
}

void GrooveBrowser::resized() {
    // Here's where we'll manage set of GrooveList children according to
    // GrooveStore::MaxDepth()
}
