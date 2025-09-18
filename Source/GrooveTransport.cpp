/*
  ==============================================================================

    GrooveTransport.cpp
    Created: 6 Sep 2025 10:29:26am
    Author:  evan

  ==============================================================================
*/

#include "GrooveTransport.h"

void GrooveTransport::initialize(File f) {
    mMidiFile.clear();

    auto fileInStream = FileInputStream(f);
    mMidiFile.readFrom(fileInStream);

    mMidiFile.convertTimestampTicksToSeconds();

    mNumTracks.store(mMidiFile.getNumTracks());
    MYDBG(__FUNCTION__"(): found " + std::to_string(mNumTracks.load()) + " channels");

    mTimeFormat = mMidiFile.getTimeFormat();
    if (mTimeFormat > 0) {
        MYDBG(" time format: " + std::to_string(mTimeFormat) + " PPQ");
    }
    else {
        MYDBG(" SMPTE time format: " + std::to_string((-mTimeFormat) >> 8 & 0xFF) + ":" + std::to_string(mTimeFormat & 0xFF));
    }

    // Add all tracks to "mTracks"
    for (int idx = 0; idx < mNumTracks.load(); idx++) {
        auto track = mMidiFile.getTrack(idx);

        addTrack(*track);
    }

    parseTracks();
}

void GrooveTransport::addTrack(const MidiMessageSequence& track) {
    mTrackHeads.emplace_back(track);
}

void GrooveTransport::actionListenerCallback(const String& message) {
    GrooveActionMessage gam = json::parse(message.toStdString());

    // GroovePlayer component ActionMessages we care about...
    if (gam["component"] == "GPLYR") {
        if (gam["action"] == "TPTCTRL") {
            std::string buttonText(gam["value"]);
            MYDBG(__FUNCTION__"(): button: " + buttonText);
        }
    }
}

void GrooveTransport::parseTracks() {
    int idx{ 0 };

    for (const auto& track : mTrackHeads) {
        int numEvents = track.mTrack.getNumEvents();

        MYDBG("    track: " + std::to_string(idx++) + ", " + std::to_string(numEvents) + " events.");

        for (int i = 0; i < numEvents; i++) {
            auto event = track.mTrack.getEventPointer(i);
            auto message = event->message;

            if (message.isMetaEvent())
                parseMetaEvent(message);
            else
                parseEvent(message);
        }
    }
}

void GrooveTransport::parseMetaEvent(const MidiMessage& message) {
    if (message.isTrackNameEvent()) {
        MYDBG("       track name: " + message.getTextFromTextMetaEvent().toStdString());
    }
    else if (message.isEndOfTrackMetaEvent()) {
        MYDBG("       End-of-track");
    }
    else if (message.isTempoMetaEvent()) {
        double tempo = 60.0 / message.getTempoSecondsPerQuarterNote();
        MYDBG("       Tempo Event:  Tempo: " + std::to_string(tempo));
    }
    else if (message.isTimeSignatureMetaEvent()) {
        message.getTimeSignatureInfo(mTimeSigNum, mTimeSigDen);
        MYDBG("       Time Signature: " + std::to_string(mTimeSigNum) + " / " + std::to_string(mTimeSigDen));
    }
    else {
        std::stringstream ss;
        ss << std::hex << message.getMetaEventType();
        std::string hexStr = ss.str();
        MYDBG("       meta, type: " + hexStr + ", ts: " + String::formatted("%0.4f", message.getTimeStamp()).toStdString());
    }
}

void GrooveTransport::parseEvent(const MidiMessage& message) {
    MYDBG("      event: " + message.getDescription().toStdString() + ", ts: " + String::formatted("%0.4f", message.getTimeStamp()).toStdString());
}

void GrooveTransport::processMidi(
    const Optional<AudioPlayHead::PositionInfo>& posInfo,
    int numSamples,
    MidiBuffer& midiMessages)
{
    if (!posInfo.hasValue()) {
        MYDBG(__FUNCTION__"(): missing PositionInfo");
        return;
    }

    // if not playing there's nothing to do
    if (!posInfo->getIsPlaying())
        return;

    // use time-in-seconds to specify the temporal window bounds 
    // of the current play head.
    double startTime = posInfo->getTimeInSeconds().orFallback(0.0);
    double endTime = startTime + (numSamples / mSampleRate);

    // for all the tracks we have (that were in the MIDI file)...
    for (const auto& trackHead : mTrackHeads) {
        //.. starting from where we left off from previous call..
        auto& message = trackHead.mTrack.getEventPointer(trackHead.mNextEventIdx)->message;
        double eventTime = message.getTimeStamp();

        if (eventTime < startTime) {
            MYDBG(__FUNCTION__"(): oopsie!  Seems like an event got missed.");
            continue;
        }

        if (eventTime > endTime)
            continue;

        do {

        } while (eventTime < endTime);
    }
}
