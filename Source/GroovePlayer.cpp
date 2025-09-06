/*
  ==============================================================================

    GroovePlayer.cpp
    Created: 3 Sep 2025 10:44:30am
    Author:  evan

  ==============================================================================
*/

#include "GroovePlayer.h"
#include "Log.h"

GroovePlayer::GroovePlayer() {
}

GroovePlayer::~GroovePlayer() {
}

void GroovePlayer::setGrooveMidiFile(File f) {
    mMidiFile.clear();

    auto fileInStream = FileInputStream(f);
    mMidiFile.readFrom(fileInStream);

    mNumTracks.store(mMidiFile.getNumTracks());
    MYDBG(__FUNCTION__"(): found " + std::to_string(mNumTracks.load()) + " channels");

    mTimeFormat = mMidiFile.getTimeFormat();
    if (mTimeFormat > 0) {
        MYDBG(" time format: " + std::to_string(mTimeFormat) + " TPQ");
    }
    else {
        MYDBG(" SMPTE time format: " + std::to_string((-mTimeFormat) >> 8 & 0xFF) + ":" + std::to_string(mTimeFormat & 0xFF));
    }

    // Add all tracks to "mTracks"
    for (int idx = 0; idx < mNumTracks.load(); idx++)
        mTracks.add(mMidiFile.getTrack(idx));

    int idx{ 0 };
    for (const auto& track : mTracks) {
        int numEvents = track->getNumEvents();

        MYDBG("    track: " + std::to_string(idx++) + ", " + std::to_string(numEvents) + " events.");

        for (int i = 0; i < numEvents; i++) {
            auto event = track->getEventPointer(i);
            processMidiMessage(event->message);
        }
    }
}

int GroovePlayer::getNumTracks() {
    return mNumTracks.load();
}

void GroovePlayer::actionListenerCallback(const String& message) {
    GrooveActionMessage gam = json::parse(message.toStdString());
    if (gam["component"] != "GVBR" || gam["action"] != "NEWF")
        return;

    setGrooveMidiFile(File((std::string)gam["value"]));
}

void GroovePlayer::processMidiMessage(const MidiMessage& message) {
    if (message.isMetaEvent()) {
        processMetaEvent(message);
    }
    else {
        MYDBG("      event: " + message.getDescription().toStdString() + ", ts: " + String::formatted("%0.4f", message.getTimeStamp()).toStdString());
    }
}

void GroovePlayer::processMetaEvent(const MidiMessage& message) {
    if (message.isTrackNameEvent()) {
        MYDBG("       track name: " + message.getTextFromTextMetaEvent().toStdString());
    }
    else if (message.isEndOfTrackMetaEvent()) {
        MYDBG("       End-of-track");
    }
    else if (message.isTempoMetaEvent()) {
        double tickLength = message.getTempoMetaEventTickLength(mTimeFormat);
        MYDBG("       Tempo Event: " + std::to_string(tickLength));
    }
    else {
        std::stringstream ss;
        ss << std::hex << message.getMetaEventType();
        std::string hexStr = ss.str();
        MYDBG("       meta, type: " + hexStr + ", ts: " + String::formatted("%0.4f", message.getTimeStamp()).toStdString());
    }
}