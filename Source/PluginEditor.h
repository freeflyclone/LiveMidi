/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GroovesList.h"

//==============================================================================
/**
*/
class LiveMidiAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Button::Listener
{
public:
    LiveMidiAudioProcessorEditor (LiveMidiAudioProcessor&);
    ~LiveMidiAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void buttonClicked(juce::Button* button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LiveMidiAudioProcessor& audioProcessor;

    // Create a "Show log" button (WIP)
    juce::TextButton chooseFileButton{ "Groove Selector" };

    GroovesList grooves{};

    std::unique_ptr<juce::FileChooser> mFileChooser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LiveMidiAudioProcessorEditor)
};
