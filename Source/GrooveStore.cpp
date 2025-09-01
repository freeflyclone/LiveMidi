/*
  ==============================================================================

    GrooveStore.cpp
    Created: 19 Aug 2025 2:43:05pm
    Author:  evan

  ==============================================================================
*/

#include <assert.h>
#include "GrooveStore.h"
#include "Log.h"

GrooveStore::GrooveStore() {
}

GrooveStore::~GrooveStore() {
}

void GrooveStore::Initialize(File f) {
    mRoot.Initialize(f, nullptr);

    FetchStoreFromFolder();
}

void GrooveStore::FetchStoreFromFolder() {
    mRoot.Scan();
}

void GrooveStore::Enumerate(GrooveFolder::EnumerationCb cb) {
    mRoot.Enumerate(cb);
}

GrooveFolder* GrooveStore::GetGrooveFolder(Array<int>& selector) {
    assert(selector.size());

    GrooveFolder* node = &mRoot;

    for (int i = 0; i < selector.size(); i++)
        node = node->GetChildren()[selector[i]].get();
    
    return node;
}

File* GrooveStore::GetGrooveFile(Array<int>& selector) {
    GrooveFolder* grooveFolder;
    int rowIdx = selector.getLast();

    // selector from somewhere lower in the heirarchy that points to a file
    if (selector.size() > 1) {
        selector.removeLast();

        // Truncate "selector" so we select the Groove folder one level up
        grooveFolder = GetGrooveFolder(selector);
    }
    else {
        // "selector" is referring to "root" GrooveFolder
        grooveFolder = GetRoot();
    }

    auto numChildren = grooveFolder->GetChildren().size();
    auto fpn = grooveFolder->GetSelfFile().getFullPathName().toStdString();
    rowIdx -= numChildren;

    MYDBG(__FUNCTION__"(): target is: " + fpn + std::string(File::getSeparatorString()) + grooveFolder->GetFileNames()[rowIdx].toStdString());

    return nullptr;
}