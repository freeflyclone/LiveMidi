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
#include "GrooveTransport.h"

using namespace juce;

class GroovePlayer : public Component, public ActionListener {
public:
    GroovePlayer(LiveMidiAudioProcessor&);
    ~GroovePlayer();

    void setGrooveMidiFile(File);

private:
    LiveMidiAudioProcessor& mAudioProcessor;

    void paint(Graphics& g) override;
    void resized() override;

    void actionListenerCallback(const String&);
};
