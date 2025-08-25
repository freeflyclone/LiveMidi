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

void GrooveFolder::Initialize(File f) {
    fileSelf = f;
    subdirNames.clear();
    fileNames.clear();

    MYDBG(__FUNCTION__" opening: " + fileSelf.getFileName().toStdString());

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

void GrooveFolder::Scan(const GrooveFolder& parentGrooveFolder) {
    if (subdirNames.size()) {
        for (const auto& subdirName : subdirNames) {
            // Create a File object for the child...
            // Figure out the absolute path for File class
            String subdirFullPathName = fileSelf.getFullPathName() + File::getSeparatorString() + subdirName;

            MYDBG(__FUNCTION__"(), considering: " + subdirFullPathName.toStdString());
            auto file = File(subdirFullPathName);

            auto child = std::make_shared<GrooveFolder>();
            child->Initialize(file);
            child->Scan(*this);
        }
    }

    if (fileNames.size()) {

    }
}
