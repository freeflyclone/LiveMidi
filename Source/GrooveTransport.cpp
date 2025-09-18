/*
  ==============================================================================

    GrooveTransport.cpp
    Created: 6 Sep 2025 10:29:26am
    Author:  evan

  ==============================================================================
*/

#include "GrooveTransport.h"

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

void GrooveTransport::processMidi(
    const Optional<AudioPlayHead::PositionInfo>& posInfo, 
    int numSamples, 
    [[maybe_unused]]MidiBuffer& midiMessages)
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
