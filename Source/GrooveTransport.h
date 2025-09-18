/*
  ==============================================================================

    GrooveTransport.h
    Created: 6 Sep 2025 10:29:26am
    Author:  evan

    GrooveTransport is the heart of the MIDI data sampler for MIDI files.

    It creates & manages a TrackPlayHead for each track in the file.
    
    Each call of ::processMidi() (driven by AudioProcessor::processBlock())
    process each track looking for MIDI events that fall within the current
    AudioPlayHead's temporal window.

    For each in-window event:
        adjust its timestamp to be relative to current AudioPlayHead time
        add it to the outgoing MidiBuffer
        increment next event index
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

    void initialize(File);
    void addTrack(const MidiMessageSequence&);

protected:
    MidiFile mMidiFile;
    TrackPlayHeads mTrackHeads;

    //std::atomic<int> mCurrentTrack;
    std::atomic<int> mNumTracks;

    short mTimeFormat{ 0 };
    int mTimeSigNum{ 4 };
    int mTimeSigDen{ 4 };

    // Near as I can tell, these are driven by the chosen audio interface.
    double mSampleRate{ 44100.0f };
    int mSamplesPerBlock{ 1024 };

    void actionListenerCallback(const String&);
    void parseTracks();
    void parseMetaEvent(const MidiMessage& message);
    void parseEvent(const MidiMessage& message);

    // Runs in the audio thread at end of LiveMidiAudioProcessor::processBlock()
    void processMidi(const Optional<AudioPlayHead::PositionInfo>& p, int, MidiBuffer&);
};