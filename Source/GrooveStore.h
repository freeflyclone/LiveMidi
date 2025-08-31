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
    GrooveStore();
    ~GrooveStore();

    void Initialize(File);
    void Enumerate(GrooveFolder::EnumerationCb);

    GrooveFolder* GetRoot() { return &mRoot; }
    GrooveFolder* GetChild(Array<int>& selector);

    int MaxDepth() { return mMaxDepth; }

protected:
    void FetchStoreFromFolder();

    GrooveFolder mRoot;
    int mMaxDepth{ 0 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GrooveStore)
};
