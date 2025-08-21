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

class GrooveStore : public Component
{
public:
    GrooveStore();
    ~GrooveStore();

    void fetchStoreFromFolder(File, int level = 0);
    void showStore();

    void paint(Graphics& g) override;
    void resized() override;

private:
    File root;
    Array<GrooveFolder> grooveFolders;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GrooveStore)
};