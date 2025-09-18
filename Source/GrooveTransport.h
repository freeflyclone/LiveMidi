/*
  ==============================================================================

    GrooveTransport.h
    Created: 6 Sep 2025 10:29:26am
    Author:  evan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GrooveActionMessage.h"
#include "Log.h"

using namespace juce;

class GrooveTransport : public ActionListener {
public:
    GrooveTransport() {};
    ~GrooveTransport() {};

protected:
    // Near as I can tell, these are driven by the chosen audio interface.
    double mSampleRate{ 44100.0f };
    int mSamplesPerBlock{ 1024 };

    // Updated in ::processMidi()
    // Reset to "0" when "Stop" message received.
    int64_t mSampleCount{ 0 };

    void actionListenerCallback(const String&);
    void processMidi(const Optional<AudioPlayHead::PositionInfo>& p, int, MidiBuffer&);
};