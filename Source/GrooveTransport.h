/*
  ==============================================================================

    GrooveTransport.h
    Created: 6 Sep 2025 10:29:26am
    Author:  evan

    GrooveTransport is the heart of the MIDI data sampler for MIDI files.

    It creates & manages a TrackPlayHead for each track in the file.
    
    Each call of ::processMidi() (driven by AudioProcessor::processBlock())
    processes each track looking for MIDI events that fall within the current
    AudioPlayHead's temporal window.

    For each in-window event:
        adjust its timestamp to be relative to current AudioPlayHead time
        add it to the outgoing MidiBuffer
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GrooveActionMessage.h"
#include "Log.h"

using namespace juce;

class GrooveTransport : public ActionListener {
public:
    typedef std::vector<MidiMessageSequence> TrackPlayHeads;

    GrooveTransport() {};
    ~GrooveTransport() {};

    void initialize(File);
    void addTrack(const MidiMessageSequence&);

protected:
    // Near as I can tell, these are driven by the chosen audio interface.
    double mSampleRate{ 44100.0f };
    int mSamplesPerBlock{ 1024 };

    MidiFile mMidiFile;
    TrackPlayHeads mTrackPlayHeads;
    short mTimeFormat{ 0 };
    int mTimeSigNum{ 4 };
    int mTimeSigDen{ 4 };

    void actionListenerCallback(const String&);

    // TODO: make these into ActionMessage broadcasters
    void parseMidiFile();
    void parseTracks();
    void parseMetaEvent(const MidiMessage& message);
    void parseEvent(const MidiMessage& message);

    // Runs in the audio thread at end of LiveMidiAudioProcessor::processBlock()
    void processMidi(const Optional<AudioPlayHead::PositionInfo>& p, int, MidiBuffer&);
};
