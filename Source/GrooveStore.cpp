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
    MYDBG(__FUNCTION__);
};

GrooveStore::~GrooveStore()
{
    MYDBG(__FUNCTION__);
};

void GrooveStore::fetchStoreFromFolder(String name)
{
    MYDBG(__FUNCTION__);

    fetchStoreFromFolder(File(name));

    return;
};

void GrooveStore::fetchStoreFromFolder(File f)
{
    MYDBG(__FUNCTION__ + std::string(": ") + f.getFileName().toStdString());

    Array<File> grooveStoreFiles = f.findChildFiles(File::findDirectories, false);

    if (!grooveStoreFiles.isEmpty())
    {
        for (const auto& storeFile : grooveStoreFiles)
        {
            fetchStoreFromFolder(f.getChildFile(storeFile.getFileName()));
        }
    }

    return;
}

void GrooveStore::paint(Graphics& g)
{
    MYDBG(__FUNCTION__);
};

void GrooveStore::resized()
{
    MYDBG(__FUNCTION__);
};
