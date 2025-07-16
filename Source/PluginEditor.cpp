/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace juce;

//==============================================================================
LiveMidiAudioProcessorEditor::LiveMidiAudioProcessorEditor (LiveMidiAudioProcessor& p)
    : AudioProcessorEditor (&p), 
    audioProcessor (p)
{
    setResizable(true, true);

    addAndMakeVisible(chooseFileButton);
    chooseFileButton.addListener(this);

    addAndMakeVisible(grooves);

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
void LiveMidiAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void LiveMidiAudioProcessorEditor::resized()
{
    MYDBG(__FUNCTION__);

    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    chooseFileButton.setBounds(10, 10, 150, 32);

    grooves.setBounds(10, 52, grooves.getWidth(), grooves.getHeight());
}

void LiveMidiAudioProcessorEditor::buttonClicked(juce::Button* button) {
    if (button == &chooseFileButton) {
        mFileChooser = std::make_unique<FileChooser>("Please select the MIDI you want to load...",
            File::getSpecialLocation(File::userHomeDirectory),
            "*.mid",
            false);

        if (mFileChooser->browseForDirectory())
        {
            File result = mFileChooser->getResult();
            MYDBG("Result: " + result.getFullPathName().toStdString());
        }
    }
}
