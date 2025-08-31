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

GrooveFolder* GrooveStore::GetChild(Array<int>& selector) {
    assert(selector.size());

    MYDBG(__FUNCTION__ "(): selector.size(): " + std::to_string(selector.size()));
    for (int i = 0; i < selector.size(); i++)
        MYDBG("   item: " + std::to_string(selector[i]));

    // TODO: navigate GrooveFolder tree using "selector"
    return nullptr;
}