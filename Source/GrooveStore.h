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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GrooveStore)
};
