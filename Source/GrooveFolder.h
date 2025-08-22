/*
  ==============================================================================

    GrooveFolder.h
    Created: 20 Aug 2025 3:27:42pm
    Author:  evan

    Helper class for storing a set of groove MIDI file names in a single folder,
    along with the relative "level" down the heirarchy from "root"
  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

using namespace juce;

class GrooveFolder {
public:
    GrooveFolder(File newFolder, int level);
    ~GrooveFolder();

    String folder;
    Array<StringArray> fileNames;
    int level;
};