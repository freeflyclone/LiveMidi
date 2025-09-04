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
    MYDBG(__FUNCTION__);
}

GroovePlayer::~GroovePlayer() {
    MYDBG(__FUNCTION__);
}

void GroovePlayer::setGrooveMidiFile(File f) {
    mMidiFile.clear();

    auto fileInStream = FileInputStream(f);
    mMidiFile.readFrom(fileInStream);

    mNumTracks.store(mMidiFile.getNumTracks());
    MYDBG(__FUNCTION__"(): found " + std::to_string(mNumTracks.load()) + " channels");

    // Add all tracks to "mTracks"
    for (int idx = 0; idx < mNumTracks.load(); idx++)
        mTracks.add(mMidiFile.getTrack(idx));

    int idx{ 0 };
    for (const auto& track : mTracks) {
        int numEvents = track->getNumEvents();

        MYDBG("    track: " + std::to_string(idx++) + ", " + std::to_string(numEvents) + " events.");

        for (int i = 0; i < numEvents; i++) {
            auto event = track->getEventPointer(i);
            MYDBG("      event: " + event->message.getDescription().toStdString());
        }
    }
}

int GroovePlayer::getNumTracks() {
    return mNumTracks.load();
}

Optional<AudioPlayHead::PositionInfo> GroovePlayer::getPosition() const {
    return mCurrentPosition;
}

void GroovePlayer::actionListenerCallback(const String& message) {
    GrooveActionMessage gam = json::parse(message.toStdString());
    if (gam["component"] != "GVBR" || gam["action"] != "NEWF")
        return;

    setGrooveMidiFile(File((std::string)gam["value"]));
}