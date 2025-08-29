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
    int xOffset{ 0 };
    int idx{ 0 };

    for (auto& listBox : mListBoxes) {
        addChildComponent(listBox);
        listBox.setTopLeftPosition(xOffset, 0);
        listBox.addActionListener(this);
        listBox.setComponentID("GrooveListBox:" + std::to_string(idx++));
        xOffset += GROOVE_LISTBOX_WIDTH - 1;
    }
}

GrooveBrowser::~GrooveBrowser() {
}

void GrooveBrowser::Initialize(File f) {
    mStore.Initialize(f);

    auto maxDepth(mStore.MaxDepth());

    for (auto& listBox : mListBoxes) {
        listBox.clear();
        listBox.setVisible(false);
    }

    mStore.Enumerate([&](GrooveFolder& gf) {
        auto& fileSelf = gf.GetSelfFile();

        for (const auto child : gf.GetChildren()) {
            mListBoxes[0].setVisible(true);
            mListBoxes[0].add(child->GetSelfFile().getFileName());
        }

        for (const auto fileName : gf.GetFileNames()) {
            mListBoxes[0].setVisible(true);
            mListBoxes[0].add(fileName);
        }
    });

    for (auto& listBox : mListBoxes)
        listBox.updateContent();

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

void GrooveBrowser::actionListenerCallback(const String& message) {
    MYDBG(__FUNCTION__ "(): " + message.toStdString());
}
