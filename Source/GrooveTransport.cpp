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

    // GroovePlayer component ActionMessages we care about...
    if (gam["component"] == "GPLYR") {
        std::string buttonText(gam["value"]);

        if (buttonText == "Play" && !mIsPlaying)
            transportPlay(true);
        else if (buttonText == "Stop" && mIsPlaying)
            transportPlay(false);
    
        MYDBG(__FUNCTION__"(): buttion: " + buttonText);
    }
}
