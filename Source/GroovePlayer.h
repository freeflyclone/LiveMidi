/*
  ==============================================================================

    GroovePlayer.h
    Created: 3 Sep 2025 10:44:30am
    Author:  evan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GrooveActionMessage.h"

using namespace juce;

class GroovePlayer : public AudioPlayHead, public ActionListener {
public:
    GroovePlayer();
    ~GroovePlayer();

    void setGrooveMidiFile(File);
    int getNumTracks();

    Optional<PositionInfo> getPosition() const override;

private:
    MidiFile mMidiFile;
    std::atomic<int> mCurrentTrack; 
    std::atomic<int> mNumTracks;
    Array<const MidiMessageSequence*> mTracks;

    PositionInfo mCurrentPosition;

    void actionListenerCallback(const String&);
};