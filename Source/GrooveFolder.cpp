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
