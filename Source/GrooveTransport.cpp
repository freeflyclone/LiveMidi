/*
  ==============================================================================

    GrooveTransport.cpp
    Created: 6 Sep 2025 10:29:26am
    Author:  evan

  ==============================================================================
*/

#include "GrooveTransport.h"

Optional<AudioPlayHead::PositionInfo> GrooveTransport::getPosition() const {
    return mPositionInfo;
}

void GrooveTransport::actionListenerCallback(const String& message) {
    GrooveActionMessage gam = json::parse(message.toStdString());
    if (gam["component"] != "GTPT")
        return;

    auto action = gam["action"];

    if (action == "PLAY") {
        mIsPlaying = true;
    }
    else if (action == "RECORDING") {
        mIsRecording = true;
    }
    else if (action == "STOP") {
        mIsPlaying = false;
        mIsRecording = false;
    }
}
