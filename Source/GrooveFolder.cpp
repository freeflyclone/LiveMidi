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
    MYDBG(__FUNCTION__" opening: " + f.getFileName().toStdString());

    auto subdirs = f.findChildFiles(File::findDirectories, false);
    for (const auto& subdir : subdirs) {
        subdirNames.add(subdir.getFileName());
        MYDBG(__FUNCTION__"  subdir: " + subdir.getFileName().toStdString());
    }

    auto files = f.findChildFiles(File::findFiles, false, "*.mid");
    for (const auto& file : files) {
        fileNames.add(file.getFileName());
        MYDBG(__FUNCTION__"    groove file: " + file.getFileName().toStdString());
    }
}

void GrooveFolder::Scan(const GrooveFolder& parent) {
    if (subdirNames.size()) {
        for (const auto& child : children) {
            // Create a File object for the child...
            // Figure out the absolute path for File class
            String parentPath = parent.fileSelf.getFullPathName();

            MYDBG(__FUNCTION__" parent: " + parentPath.toStdString());

            // Create the child object
            //auto grooveFolder = std::make_shared<GrooveFolder>();
        }
    }

    if (fileNames.size()) {

    }
}
