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
    audioProcessor (p),
    showLogButton("Show log"),
    chooseFileButton("Open MIDI file...")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    addAndMakeVisible(showLogButton);
    showLogButton.addListener(this);

    addAndMakeVisible(chooseFileButton);
    chooseFileButton.addListener(this);
}

LiveMidiAudioProcessorEditor::~LiveMidiAudioProcessorEditor()
{
}

//==============================================================================
void LiveMidiAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void LiveMidiAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    showLogButton.setBounds(10, 10, 100, 32);
    chooseFileButton.setBounds(120, 10, 150, 32);
}

void LiveMidiAudioProcessorEditor::buttonClicked(juce::Button* button) {
    if (button == &showLogButton) {
        if (!mLog)
        {
            showLogButton.setButtonText("Hide Log");
            mLog.reset(new LogWindow("Your Mom"));
        }
        else
        {
            mLog.reset(nullptr);
            showLogButton.setButtonText("Show Log");
        }
    }
    else if (button == &chooseFileButton) {
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
