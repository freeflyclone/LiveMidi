/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GrooveStore.h"

using namespace juce;

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
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LiveMidiAudioProcessor& audioProcessor;

    // Create a "Select Groove" button (WIP)
    Label groovesLabel{"groovesLabel", "Grooves: "};
    TextButton groovesButton{ TEMP_STORE_FOLDER_NAME };

    std::unique_ptr<FileChooser> mFileChooser;
    std::unique_ptr<GrooveStore> grooves;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LiveMidiAudioProcessorEditor)
};
