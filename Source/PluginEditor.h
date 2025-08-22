/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GrooveBrowser.h"

using namespace juce;

#define TEMP_STORE_FOLDER_NAME "E:/music/Native Instruments Content/Abbey Road 60s Drummer Library/MIDI Files"

//==============================================================================
/**
*/
class LiveMidiAudioProcessorEditor  : public AudioProcessorEditor, public Button::Listener
{
public:
    LiveMidiAudioProcessorEditor (LiveMidiAudioProcessor&);
    ~LiveMidiAudioProcessorEditor() override;

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void buttonClicked(Button* button) override;

private:
    // Provide this editor with access the processor object that created it.
    LiveMidiAudioProcessor& audioProcessor;

    // Create a "Select Groove" button (WIP)
    Label groovesLabel{"groovesLabel", "Grooves: "};
    TextButton groovesButton{ TEMP_STORE_FOLDER_NAME };

    std::unique_ptr<FileChooser> mFileChooser;
    std::unique_ptr<GrooveBrowser> browser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LiveMidiAudioProcessorEditor)
};
