/*
  ==============================================================================

    GrooveFolder.cpp
    Created: 20 Aug 2025 3:27:42pm
    Author:  evan

  ==============================================================================
*/

#include "GrooveFolder.h"
#include "Log.h"

GrooveFolder::GrooveFolder(File f, int l) 
    : folder(f.getFileName().toStdString()),
    level(l)
{
    auto children = f.findChildFiles(File::findFiles, false, "*.mid");

    for (const auto& child : children)
        fileNames.add(child.getFileName());
}

GrooveFolder::~GrooveFolder()
{
}
