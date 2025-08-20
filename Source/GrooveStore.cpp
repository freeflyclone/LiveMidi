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

void GrooveStore::fetchStoreFromFolder(File f)
{
    MYDBG(__FUNCTION__ + std::string(": ") + f.getFileName().toStdString());

    folders.clear();
    files.clear();

    // assume child folders, recursively search them
    folders = f.findChildFiles(File::findDirectories, true);

    // Early bail if no children, FIX THIS: we'll miss top-level files this way.
    if (folders.isEmpty())
        return;

    // Scan child folders
    for (const auto& folder : folders)
    {
        // always add StringArray so # of StringArray matches # of File
        auto strings = std::make_unique<StringArray>();

        // enumerate any .mid files in the folder
        auto names = folder.findChildFiles(File::findFiles, false, "*.mid");

        // store the names of the files
        for (const auto& name : names)
            strings->add(name.getFileName());

        // Add (possibly empty) list of files
        files.add(*strings);
    }

    // report what was found to DBG output
    for(int i=0; i<files.size(); i++)
    {
        MYDBG("Folder: " + folders[i].getRelativePathFrom(f).toStdString());
        for (const auto& name : files[i])
        {
            MYDBG("    " + name.toStdString());
        }
    }
}

void GrooveStore::paint(Graphics& g)
{
}

void GrooveStore::resized()
{
}
