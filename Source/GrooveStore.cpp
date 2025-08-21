/*
  ==============================================================================

    GrooveStore.cpp
    Created: 19 Aug 2025 2:43:05pm
    Author:  evan

  ==============================================================================
*/

#include "GrooveStore.h"
#include "Log.h"

GrooveStore::GrooveStore()
{
}

GrooveStore::~GrooveStore()
{
}

void GrooveStore::fetchStoreFromFolder(File f, int level)
{
    if (level == 0) {
        root = f;
        grooveFolders.clear();
    }

    auto gf = std::make_unique<GrooveFolder>(f, level);

    grooveFolders.add(*gf);

    auto folders = f.findChildFiles(File::findDirectories, false);

    for (const auto& folder : folders) {
        level++;
        fetchStoreFromFolder(folder, level);
        level--;
    }

    if (level > maxDepth)
        maxDepth = level;
}

void GrooveStore::Enumerate(EnumerationCb cb)
{
    for (const GrooveFolder& gf : grooveFolders) {
        cb(gf);
    }
}

void GrooveStore::showStore()
{
    for (const auto& gf : grooveFolders)
    {
        MYDBG(__FUNCTION__ + std::string(": ") + std::to_string(gf.level) + ", " + gf.folder);

        for (const auto& filename : gf.files)
            MYDBG(__FUNCTION__ + std::string(": ") + std::to_string(gf.level)+ ",   " + filename);
    }
}
