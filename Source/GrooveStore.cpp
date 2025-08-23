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
    FetchStoreFromFolder(f);
}

void GrooveStore::FetchStoreFromFolder(File f, int level) {
    // when called by Initialize(): clear previous data
    if (level == 0) {
        root = f;
        folders.clear();
        maxDepth = 0;
    }

    // GrooveFolder() fills its "fileNames" Array if
    // MIDI files are found in its "folder" 
    GrooveFolder gf = GrooveFolder(f, level);

    // always add (possibly place-holder only) new GrooveFolder instance;
    folders.add(gf);

    // Recurse into child folders if present
    auto childFolders = f.findChildFiles(File::findDirectories, false);
    for (const auto& folder : childFolders)
        FetchStoreFromFolder(folder, level + 1);

    // Track max depth
    if (level > maxDepth)
        maxDepth = level;
}

void GrooveStore::Enumerate(EnumerationCb cb) {
    for (const GrooveFolder& f : folders)
        cb(f);
}