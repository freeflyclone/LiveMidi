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

class GrooveTransport : public AudioPlayHead, public ActionListener {
public:
    GrooveTransport() {};
    ~GrooveTransport() {};

    Optional<PositionInfo> getPosition() const;
    bool canControlTransport() override { return true; }
    void transportPlay(bool shouldStart) { mIsPlaying = shouldStart; };
    void transportRecord(bool shouldStart) { mIsRecording = shouldStart; };

protected:
    PositionInfo mPositionInfo;
    bool mIsPlaying{ false };
    bool mIsRecording{ false };

    // Updated in AudioProcessor::processBlock() when "mIsPlaying" is true.
    // Reset to "0" when "Stop" message received.
    int mSampleCount{ 0 };

    void actionListenerCallback(const String&);
    void updateCurrentPosition(int);
};