/*
  ==============================================================================

    GrooveBrowser.h
    Created: 22 Aug 2025 10:37:17am
    Author:  evan

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "GrooveStore.h"
#include "GrooveListBox.h"

using namespace juce;

#define TEMP_STORE_FOLDER_NAME "E:/music/Native Instruments Content/Abbey Road 60s Drummer Library/MIDI Files"

class GrooveBrowser : public Component, public ActionListener {
public:
    GrooveBrowser();
    ~GrooveBrowser();

    void Initialize(File);
    void actionListenerCallback(const String&) override;

protected:
    void paint(Graphics& g) override;
    void resized() override;

    GrooveStore mStore;

    GrooveListBox mListBoxes[6];
};