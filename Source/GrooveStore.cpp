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
    root.Initialize(f);

    FetchStoreFromFolder(f);
}

void GrooveStore::FetchStoreFromFolder(File f, int level) {
}

void GrooveStore::Enumerate(EnumerationCb cb) {
}