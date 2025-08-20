/*
  ==============================================================================

    GrooveFolder.h
    Created: 20 Aug 2025 3:27:42pm
    Author:  evan

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

using namespace juce;

class GrooveFolder : public Component {
public:
    GrooveFolder(File);
    ~GrooveFolder();

private:
    File folder;
    Array<File> files;
};