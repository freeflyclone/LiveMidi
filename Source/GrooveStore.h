/*
  ==============================================================================

    GrooveStore.h
    Created: 19 Aug 2025 2:43:05pm
    Author:  evan

    A class for managing a tree of GrooveFolder's, each of which may contain MIDI
    groove files (drum patterns, ostinatos, whatever) and/or sub-directories
    leading to MIDI files.
  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "GrooveFolder.h"

using namespace juce;

class GrooveStore
{
public:
    typedef std::function<void(const GrooveFolder&)> EnumerationCb;

    GrooveStore();
    ~GrooveStore();

    void Initialize(File);
    void Enumerate(EnumerationCb);

    int MaxDepth() { return maxDepth; }

protected:
    void FetchStoreFromFolder(File, int level = 0);

    GrooveFolder root;
    int maxDepth{ 0 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GrooveStore)
};
