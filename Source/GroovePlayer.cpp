/*
  ==============================================================================

    GroovePlayer.cpp
    Created: 3 Sep 2025 10:44:30am
    Author:  evan

  ==============================================================================
*/

#include "GroovePlayer.h"
#include "Log.h"

namespace {
    int nsComponentID{ 0 };
};

GroovePlayer::GroovePlayer(LiveMidiAudioProcessor& p)
    : mAudioProcessor(p)
{
    int xOffset{ 0 };
    int idx{ 0 };

    setName("GPLYR");
    setComponentID(String::formatted("%02d", nsComponentID++));

    for (auto& listBox : mListBoxes) {
        addChildComponent(listBox);
        listBox.setTopLeftPosition(xOffset, 0);
        listBox.addActionListener(this);
        listBox.setName("GLVWR");
        listBox.setComponentID(std::to_string(idx++));
        xOffset += GROOVE_LISTBOX_WIDTH - 1;
    }
}

GroovePlayer::~GroovePlayer() {
}

void GroovePlayer::viewSelectedMidiFile(const File& f) {
    for (auto& listBox : mListBoxes) {
        listBox.clear();
        listBox.setVisible(false);
        listBox.deselectAllRows();
    }

    auto& listBox = mListBoxes[0];

    listBox.setVisible(true);
    listBox.add(f.getFileNameWithoutExtension());
    listBox.updateContent();

    repaint();
}

void GroovePlayer::paint(Graphics& g) {
    g.fillAll(Colour(0xff2f2f2f));
}

void GroovePlayer::resized() {
    mListBoxes[0].setSize(GROOVE_LISTBOX_WIDTH, getHeight());
}

void GroovePlayer::setGrooveMidiFile(File f) {
    mAudioProcessor.initialize(f);
    viewSelectedMidiFile(f);
}

void GroovePlayer::actionListenerCallback(const String& message) {
    GrooveActionMessage gam = json::parse(message.toStdString());

    // process Browser's "NEWF" message.
    if (gam["component"] == "GVBR" && gam["action"] == "NEWF") {
        setGrooveMidiFile(File((std::string)gam["value"]));
    }
    else {
        MYDBG(__FUNCTION__"(): unrecognized message: " + message.toStdString());
    }
}
