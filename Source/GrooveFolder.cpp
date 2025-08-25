/*
  ==============================================================================

    GrooveFolder.cpp
    Created: 20 Aug 2025 3:27:42pm
    Author:  evan

  ==============================================================================
*/

#include "GrooveFolder.h"
#include "Log.h"

GrooveFolder::GrooveFolder() 
{
}

GrooveFolder::~GrooveFolder()
{
}

void GrooveFolder::Initialize(File f, GrooveFolderPtr p) {
    fileSelf = f;
    subdirNames.clear();
    fileNames.clear();
    parent = p;

    auto subdirs = fileSelf.findChildFiles(File::findDirectories, false);
    for (const auto& subdir : subdirs) {
        subdirNames.add(subdir.getFileName());
        MYDBG(__FUNCTION__"  subdir: " + subdir.getFileName().toStdString());
    }

    auto files = fileSelf.findChildFiles(File::findFiles, false, "*.mid");
    for (const auto& file : files) {
        fileNames.add(file.getFileName());
        MYDBG(__FUNCTION__"    groove file: " + file.getFileName().toStdString());
    }
}

void GrooveFolder::Scan() {
    if (subdirNames.size()) {
        for (const auto& subdirName : subdirNames) {
            // Create a File object for the child...
            // Figure out the absolute path for File class
            String subdirAbsolutePathName = fileSelf.getFullPathName() + File::getSeparatorString() + subdirName;

            MYDBG(__FUNCTION__"(), considering: " + subdirAbsolutePathName.toStdString());
            auto file = File(subdirAbsolutePathName);

            auto child = std::make_shared<GrooveFolder>();
            child->Initialize(file, parent);
            child->Scan();
        }
    }

    if (fileNames.size()) {

    }
}
