/*
  ==============================================================================

    GroovePlayer.h
    Created: 3 Sep 2025 10:44:30am
    Author:  evan

  ==============================================================================
*/

#pragma once
#include <sstream>
#include <iomanip>
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GrooveActionMessage.h"
#include "GrooveListBox.h"
#include "GrooveTransport.h"

using namespace juce;

class GroovePlayer : public Component, public ActionListener, public ActionBroadcaster {
public:
    GroovePlayer(LiveMidiAudioProcessor&);
    ~GroovePlayer();

    void setGrooveMidiFile(File);
    void viewSelectedMidiFile(const File&);

private:
    LiveMidiAudioProcessor& mAudioProcessor;
    GrooveListBox mListBoxes[3];

    void paint(Graphics& g) override;
    void resized() override;

    void actionListenerCallback(const String&);
};
