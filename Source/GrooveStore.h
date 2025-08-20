/*
  ==============================================================================

    GrooveStore.h
    Created: 19 Aug 2025 2:43:05pm
    Author:  evan

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "GrooveList.h"

#define TEMP_STORE_FOLDER_NAME "E:/music/Native Instruments Content/Abbey Road 60s Drummer Library/MIDI Files/Late Kit"

using namespace juce;

class GrooveStore : public Component
{
public:
    GrooveStore();
    ~GrooveStore();

    void fetchStoreFromFolder(String);
    void fetchStoreFromFolder(File);

    void paint(Graphics& g) override;
    void resized() override;

private:
    std::unique_ptr<Array<std::unique_ptr<GrooveStore>>> stores;
    std::unique_ptr<GrooveList> grooves;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GrooveStore)
};