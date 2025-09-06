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
#include "GrooveTransport.h"

using namespace juce;

class GroovePlayer : public ActionListener, public GrooveTransport {
public:
    GroovePlayer();
    ~GroovePlayer();

    void setGrooveMidiFile(File);
    int getNumTracks();

    void processMidiMessage(const MidiMessage& event);
    void processMetaEvent(const MidiMessage& event);

private:
    MidiFile mMidiFile;
    std::atomic<int> mCurrentTrack; 
    std::atomic<int> mNumTracks;

    short mTimeFormat{ 0 };
    int mTimeSigNum{ 4 };
    int mTimeSigDen{ 4 };

    Array<const MidiMessageSequence*> mTracks;

    void actionListenerCallback(const String&);
};