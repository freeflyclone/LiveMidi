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

void GrooveTransport::processMidi(
    Optional<AudioPlayHead::PositionInfo>* positionInfo, 
    [[maybe_unused]]int numSamples, 
    [[maybe_unused]]MidiBuffer& midiMessages)
{
    auto posInfo = *positionInfo;
    if (!posInfo.hasValue()) {
        MYDBG(__FUNCTION__"(): missing PositionInfo");
        return;
    }

    mSampleCount = posInfo->getTimeInSamples().orFallback(0);

    if (posInfo->getIsPlaying()) {
        MYDBG(__FUNCTION__"():  mSampleCount: " + std::to_string(mSampleCount));
    }
}
