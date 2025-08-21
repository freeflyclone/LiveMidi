/*
  ==============================================================================

    GrooveStore.h
    Created: 19 Aug 2025 2:43:05pm
    Author:  evan

    A class for managing a tree of GrooveFolder's, each of which contains MIDI
    groove files (drum patterns, ostinatos, whatever)
  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "GrooveList.h"
#include "GrooveFolder.h"

#define TEMP_STORE_FOLDER_NAME "E:/music/Native Instruments Content/Abbey Road 60s Drummer Library/MIDI Files/Late Kit"

using namespace juce;

class GrooveStore
{
public:
    typedef std::function<void(const GrooveFolder&)> EnumerationCb;

    GrooveStore();
    ~GrooveStore();

    void fetchStoreFromFolder(File, int level = 0);
    void Enumerate(EnumerationCb);
    int MaxDepth() { return maxDepth; }
    void showStore();

protected:
    File root;
    Array<GrooveFolder> grooveFolders;
    int maxDepth{ 0 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GrooveStore)
};