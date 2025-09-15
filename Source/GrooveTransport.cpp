/*
  ==============================================================================

    GrooveTransport.cpp
    Created: 6 Sep 2025 10:29:26am
    Author:  evan

  ==============================================================================
*/

#include "GrooveTransport.h"

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

void GrooveTransport::processMidi(Optional<AudioPlayHead::PositionInfo>& posInfo, int numSamples, MidiBuffer& midiMessages) {
    if (!posInfo.hasValue()) {
        MYDBG(__FUNCTION__"(): mHostPlayHead returned NO value for PositionInfo");
        return;
    }

    mSampleCount = posInfo->getTimeInSamples().orFallback(0);

    if (posInfo->getIsPlaying()) {
        MYDBG(__FUNCTION__"():  mSampleCount: " + std::to_string(mSampleCount));
    }
}
