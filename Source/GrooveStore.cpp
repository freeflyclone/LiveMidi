/*
  ==============================================================================

    GrooveStore.cpp
    Created: 19 Aug 2025 2:43:05pm
    Author:  evan

  ==============================================================================
*/

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