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
    LiveMidiAudioProcessor& mAudioProcessor;

    // Create a "Select Groove" button (WIP)
    Label mGroovesLabel{"groovesLabel", "Grooves: "};
    TextButton mGroovesButton{ TEMP_STORE_FOLDER_NAME };

    GrooveBrowser mBrowser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LiveMidiAudioProcessorEditor)
};
