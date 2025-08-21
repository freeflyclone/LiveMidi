/*
  ==============================================================================

    GrooveStore.cpp
    Created: 19 Aug 2025 2:43:05pm
    Author:  evan

  ==============================================================================
*/

#include "GrooveStore.h"
#include "Log.h"

#define XYZZY_PREFIX "buttonClicked::lambda"

GrooveStore::GrooveStore() 
{
    MYDBG(__FUNCTION__);
}

GrooveStore::~GrooveStore() 
{
    MYDBG(__FUNCTION__);
}

void GrooveStore::Initialize(File f)
{
    MYDBG(__FUNCTION__);

    FetchStoreFromFolder(f);

    Enumerate([&](const GrooveFolder& gf) {
        std::string indentation(": ");

        if (gf.level == 0)
            MYDBG(XYZZY_PREFIX + indentation + gf.folder + ", maxDepth: " + std::to_string(maxDepth));
        else {
            for (int i = 0; i < gf.level; i++)
                indentation += "  ";

            MYDBG(XYZZY_PREFIX + indentation + "   " + gf.folder);

            for (const auto& file : gf.files) {
                MYDBG(XYZZY_PREFIX + indentation + "      " + file);
            }
        }
    });
}

void GrooveStore::FetchStoreFromFolder(File f, int level) 
{
    // when called by Initialize(): clear stale data
    if (level == 0) {
        root = f;
        grooveFolders.clear();
        maxDepth = 0;
    }

    // smart ptr for new GrooveFolder instance eases management.
    // 
    // GrooveFolder() fills its "files" vector if
    // MIDI files are found in its "folder" 
    auto gf = std::make_unique<GrooveFolder>(f, level);

    // always add new GrooveFolder instance;
    grooveFolders.add(*gf);

    // Recurse into child folders if present
    auto folders = f.findChildFiles(File::findDirectories, false);
    for (const auto& folder : folders)
        FetchStoreFromFolder(folder, level+1);

    // Track max depth
    if (level > maxDepth)
        maxDepth = level;
}

void GrooveStore::Enumerate(EnumerationCb cb) {
    for (const GrooveFolder& gf : grooveFolders)
        cb(gf);
}

void GrooveStore::ShowStore()
{
    for (const auto& gf : grooveFolders) {
        MYDBG(__FUNCTION__ + std::string(": ") + std::to_string(gf.level) + ", " + gf.folder);

        for (const auto& filename : gf.files)
            MYDBG(__FUNCTION__ + std::string(": ") + std::to_string(gf.level)+ ",   " + filename);
    }
}
