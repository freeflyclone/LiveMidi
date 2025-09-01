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
        listBox.setName("GLBX");
        listBox.setComponentID(std::to_string(idx++));
        xOffset += GROOVE_LISTBOX_WIDTH - 1;
    }
}

GrooveBrowser::~GrooveBrowser() {
}

void GrooveBrowser::Initialize(File f) {
    mStore.Initialize(f);

    for (auto& listBox : mListBoxes) {
        listBox.clear();
        listBox.setVisible(false);
    }

    mStore.Enumerate([&](GrooveFolder& gf) {
        auto& listBox = mListBoxes[0];

        for (const auto child : gf.GetChildren()) {
            listBox.setVisible(true);
            listBox.add(child->GetSelfFile().getFileName());
        }

        for (const auto fileName : gf.GetFileNames()) {
            listBox.setVisible(true);
            listBox.add(fileName);
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
    GrooveActionMessage gam = json::parse(message.toStdString());

    if (gam["component"] != "GLBX" || gam["action"] != "SRC")
        return;

    HandleSelectionChangeAction(gam);
}

// Third pass at using the GrooveStore data for navigation.  WIP
// Using new GrooveStore::GetGrooveFolder() works great!
//
// NOTE: it is assumed that JUCE calls this only with valid input. 
void GrooveBrowser::HandleSelectionChangeAction(GrooveActionMessage& gam) {
    int boxIdx = gam["index"];
    int rowIdx = gam["value"];

    // Handle cases where selection occurs in higher level box
    // when lower level box(es) is(are) present.
    if (rowIdx < 0) {
        auto& box = mListBoxes[boxIdx + 1];

        box.clear();
        box.updateContent();
        box.setVisible(false);

        return;
    }

    // Build selector from chain of mListBoxes' current selected row(s)
    Array<int> selector;
    for (int idx = 0; idx <= boxIdx; idx++)
        selector.add(mListBoxes[idx].getSelectedRow());

    // This WILL be null if user clicks on a MIDI file somewhere in the tree.
    GrooveFolder* grooveFolder = mStore.GetGrooveFolder(selector);

    if (!grooveFolder) {
        // selector from somewhere lower in the heirarchy that points to a file
        if (selector.size() > 1) {
            selector.removeLast();

            // Truncate "selector" so we select the Groove folder one level up
            grooveFolder = mStore.GetGrooveFolder(selector);
        }
        else {
            // "selector" is referring to "root" GrooveFolder
            grooveFolder = mStore.GetRoot();
        }

        auto numChildren = grooveFolder->GetChildren().size();
        auto fpn = grooveFolder->GetSelfFile().getFullPathName().toStdString();
        rowIdx -= numChildren;

        MYDBG(__FUNCTION__"(): target is: " + fpn + std::string(File::getSeparatorString()) + grooveFolder->GetFileNames()[rowIdx].toStdString());

        return;
    }

    grooveFolder->Enumerate([&](GrooveFolder& gf) {
        auto& box = mListBoxes[boxIdx + 1];

        box.clear();
        box.updateContent();

        for (const auto& name : gf.GetSubdirNames())
            box.add(name);

        for (const auto& name : gf.GetFileNames())
            box.add(name);

        box.updateContent();
        box.setVisible(true);
    });
}
