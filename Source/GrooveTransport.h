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
    // TrackPlayHead provides real-time "next event" index per track whilst actually playing,
    // and a const reference to the actual MIDI sequence data for that track
    struct TrackPlayHead {
        int mNextEventIdx{ 0 };
        const MidiMessageSequence& mTrack;

        TrackPlayHead(const MidiMessageSequence& track) : mTrack(track) {};
    };
    typedef std::vector<TrackPlayHead> TrackPlayHeads;

    GrooveTransport() {};
    ~GrooveTransport() {};

    void addTrack(const MidiMessageSequence&);

protected:
    TrackPlayHeads mTrackHeads;

    // Near as I can tell, these are driven by the chosen audio interface.
    double mSampleRate{ 44100.0f };
    int mSamplesPerBlock{ 1024 };

    // Updated in ::processMidi()
    // Reset to "0" when "Stop" message received.
    int64_t mCurrentSampleClock{ 0 };

    void actionListenerCallback(const String&);
    void processMidi(const Optional<AudioPlayHead::PositionInfo>& p, int, MidiBuffer&);
};