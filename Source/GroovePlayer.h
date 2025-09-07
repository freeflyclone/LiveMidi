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

class GroovePlayer : public Component, public ActionListener, public ActionBroadcaster {
public:
    GroovePlayer(GrooveTransport&);
    ~GroovePlayer();

    void setGrooveMidiFile(File);
    int getNumTracks();

    void processMidiMessage(const MidiMessage& event);
    void processMetaEvent(const MidiMessage& event);

private:
    GrooveTransport& mTransport;
    MidiFile mMidiFile;
    std::atomic<int> mCurrentTrack; 
    std::atomic<int> mNumTracks;

    short mTimeFormat{ 0 };
    int mTimeSigNum{ 4 };
    int mTimeSigDen{ 4 };

    Array<const MidiMessageSequence*> mTracks;

    TextButton mStartButton{ " Start " };
    TextButton mMinusMeasure{ " -Meas " };
    TextButton mStopButton{ " Stop " };
    TextButton mPauseButton{ " Pause " };
    TextButton mPlusMeasure{ " +Meas " };
    TextButton mEndButton{ " End " };

    void paint(Graphics& g) override;
    void resized() override;

    void actionListenerCallback(const String&);
};