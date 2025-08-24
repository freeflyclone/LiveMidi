/*
  ==============================================================================

    GrooveFolder.h
    Created: 20 Aug 2025 3:27:42pm
    Author:  evan

    Helper class for storing a set of groove MIDI file names in a single folder,
    the set of subdirs found (possibly containing additional MIDI files),    
    along with the relative "level" down the heirarchy from the "root" folder.
  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

using namespace juce;

class GrooveFolder : public Component {
public:
    GrooveFolder();
    ~GrooveFolder();

    // Load up all "*.mid" file and subfolder names non-recursively
    void Initialize(File);

    Array<StringArray> fileNames;
    Array<StringArray> subdirNames;
    int level{ 0 };
};