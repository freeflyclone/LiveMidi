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
        listBox.setComponentID("GLBX:" + std::to_string(idx++));
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
    auto end = message.fromLastOccurrenceOf(":", false, true);

    String classCode = message.substring(0, 4);
    String classIndex = message.substring(5, 6);
    String actionCode = message.substring(7, 11);
    String actionIndex = message.substring(11);
    int aIdx = actionIndex.getIntValue();

    MYDBG(__FUNCTION__ "(): " + message.toStdString() + ", end: " + end.toStdString());
    MYDBG(__FUNCTION__ "(): classCode: " + classCode.toStdString() + ", classIndex: " + classIndex.toStdString() + ", actionCode: " + actionCode.toStdString() + ", actionIndex: " + actionIndex.toStdString());

    GrooveFolder* root = mStore.GetRoot();
    auto grooveFilePtrs = root->GetChildren();

    int numChildren = grooveFilePtrs.size();

    if (aIdx < numChildren) {
        GrooveFolder::GrooveFolderPtr grooveFilePtr = grooveFilePtrs[aIdx];
        auto& fullPath = grooveFilePtr->GetSelfFile().getFullPathName();

        MYDBG(__FUNCTION__ "(): " + std::to_string(numChildren) + 
            ", aIdx: " + std::to_string(aIdx) + 
            ", fullPath: " + fullPath.toStdString());
    }
}
