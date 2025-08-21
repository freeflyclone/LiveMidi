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

    level++;
    for (const auto& folder : folders)
        fetchStoreFromFolder(folder, level);
}

void GrooveStore::showStore()
{
    for (const auto& gf : grooveFolders)
    {
        std::string indentation(": ");

        for (int i = 0; i < gf.level; i++)
            indentation += "   ";

        MYDBG(__FUNCTION__ + indentation + gf.folder);

        for (const auto& filename : gf.files) {
            MYDBG(__FUNCTION__ + indentation + "   " + filename);
        }
    }
}

void GrooveStore::paint(Graphics& g)
{
}

void GrooveStore::resized()
{
}
