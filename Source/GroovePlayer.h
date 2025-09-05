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
#include "GrooveActionMessage.h"

using namespace juce;

class GroovePlayer : public AudioPlayHead, public ActionListener {
public:
    GroovePlayer();
    ~GroovePlayer();

    void setGrooveMidiFile(File);
    int getNumTracks();

    void processMidiMessage(const MidiMessage& event);
    void processMetaEvent(const MidiMessage& event);

    Optional<PositionInfo> getPosition() const override;

private:
    MidiFile mMidiFile;
    std::atomic<int> mCurrentTrack; 
    std::atomic<int> mNumTracks;

    short mTimeFormat{ 0 };

    Array<const MidiMessageSequence*> mTracks;

    PositionInfo mCurrentPosition;

    void actionListenerCallback(const String&);
};