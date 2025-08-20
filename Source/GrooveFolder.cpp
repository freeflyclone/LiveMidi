/*
  ==============================================================================

    GrooveFolder.cpp
    Created: 20 Aug 2025 3:27:42pm
    Author:  evan

  ==============================================================================
*/

#include "GrooveFolder.h"
#include "Log.h"

GrooveFolder::GrooveFolder(File f) :
    folder(f)
{
    files = f.findChildFiles(File::findFiles, false, "*.mid");
}

GrooveFolder::~GrooveFolder()
{
}
