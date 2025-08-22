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

    // smart ptr for new GrooveFolder instance eases management.
    // 
    // GrooveFolder() fills its "files" vector if
    // MIDI files are found in its "folder" 
    auto gf = std::make_unique<GrooveFolder>(f, level);

    // always add (possibly place-holder only) new GrooveFolder instance;
    folders.add(*gf);

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

void GrooveStore::ShowStore() {
    for (const auto& gf : folders) {
        MYDBG(__FUNCTION__ + std::string(": ") + std::to_string(gf.level) + ", " + gf.folder);

        for (const auto& filename : gf.fileNames)
            MYDBG(__FUNCTION__ + std::string(": ") + std::to_string(gf.level)+ ",   " + filename);
    }
}
