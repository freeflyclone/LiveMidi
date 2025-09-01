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