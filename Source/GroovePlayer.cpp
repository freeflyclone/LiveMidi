/*
  ==============================================================================

    GroovePlayer.cpp
    Created: 3 Sep 2025 10:44:30am
    Author:  evan

  ==============================================================================
*/

#include "GroovePlayer.h"
#include "Log.h"

GroovePlayer::GroovePlayer(LiveMidiAudioProcessor& p)
    : mAudioProcessor(p)
{
    setName("GPLYR");
    setComponentID("0");
}

GroovePlayer::~GroovePlayer() {
}

void GroovePlayer::paint(Graphics& g) {
    g.fillAll(Colour(0xffcf00cf));
}

void GroovePlayer::resized() {
}

void GroovePlayer::setGrooveMidiFile(File f) {
    mAudioProcessor.initialize(f);
}

void GroovePlayer::actionListenerCallback(const String& message) {
    GrooveActionMessage gam = json::parse(message.toStdString());

    // Ignore message if it isn't from GrooveBrowser or isn't a "NewFile" action
    if (gam["component"] != "GVBR" || gam["action"] != "NEWF")
        return;

    setGrooveMidiFile(File((std::string)gam["value"]));
}
