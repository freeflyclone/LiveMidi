/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
LiveMidiAudioProcessorEditor::LiveMidiAudioProcessorEditor (LiveMidiAudioProcessor& p)
    : AudioProcessorEditor (&p), 
    audioProcessor (p)
{
    setResizable(true, true);

    addAndMakeVisible(groovesLabel);
    addAndMakeVisible(groovesButton);
    groovesButton.addListener(this);

    grooves = std::make_unique<GrooveStore>();

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    // 
    // SOHN: do setSize() last!
    setSize (600, 300);
}

LiveMidiAudioProcessorEditor::~LiveMidiAudioProcessorEditor()
{
}

//==============================================================================
void LiveMidiAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void LiveMidiAudioProcessorEditor::resized()
{
    Rectangle area = getLocalBounds();
    auto width = area.getWidth();

    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto text = groovesLabel.getText();

    const Font labelFont = groovesLabel.getFont();
    const auto textWidth = GlyphArrangement::getStringWidth(labelFont, groovesLabel.getText());
    const auto textHeight = labelFont.getHeight();

    groovesLabel.setBounds(10, 20, textWidth, textHeight);
    groovesButton.setBounds(20 + textWidth, 10, width - textWidth - 30, 32);
}


void LiveMidiAudioProcessorEditor::buttonClicked(Button* button) {
    if (button == &groovesButton) {

        mFileChooser = std::make_unique<FileChooser>("Please select the MIDI you want to load...",
            button->getButtonText(),
            "*.mid",
            false);

        if (mFileChooser->browseForDirectory())
            grooves->Initialize(mFileChooser->getResult());
    }
}
