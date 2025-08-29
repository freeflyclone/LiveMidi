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
    root.Initialize(f, nullptr);

    FetchStoreFromFolder();
}

void GrooveStore::FetchStoreFromFolder() {
    root.Scan();
}

void GrooveStore::Enumerate(GrooveFolder::EnumerationCb cb) {
    root.Enumerate(cb);
}