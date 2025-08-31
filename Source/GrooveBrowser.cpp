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
    json jActionMessage = json::parse(message.toStdString());

    if (jActionMessage["component"] != "GLBX" || jActionMessage["action"] != "SRC")
        return;

    HandleSelectionChangeAction(jActionMessage);
}

// Second pass at using the GrooveStore data for navigation.  WIP
// Need to generalize GrooveFolder tree navigation to make it comprehensible.
void GrooveBrowser::HandleSelectionChangeAction(json& jam) {
    static int evenOdd{ 0 };

    MYDBG(__FUNCTION__ "(): " + jam.dump());

    int boxIdx = jam["index"];
    int rowIdx = jam["value"];

    auto& grooveFolderPtrs = mStore.GetRoot()->GetChildren();
    int numChildren = grooveFolderPtrs.size();

    if (boxIdx > 0) {
        Array<int> selector;

        for (int idx = boxIdx; idx >= 0; idx--)
            selector.insert(0, mListBoxes[idx].getSelectedRow());

        auto grooveFolderPointer = mStore.GetChild(selector);

        // TODO: use "grooveFolderPointer" from GrooveStore::GetChild() appropriately
    }

    if (rowIdx < numChildren) {
        GrooveFolder::GrooveFolderPtr grooveFolderPtr = grooveFolderPtrs[rowIdx];

        grooveFolderPtr->Enumerate([&](GrooveFolder& gf) {
            MYDBG("  enumerating: " + gf.GetSelfFile().getFileName().toStdString());

            auto& box = mListBoxes[boxIdx + 1];

            box.clear();

            for (const auto& name : gf.GetSubdirNames())
                box.add(name);

            for (const auto& name : gf.GetFileNames())
                box.add(name);

            box.updateContent();
            box.setVisible(true);
        });
    }
}
