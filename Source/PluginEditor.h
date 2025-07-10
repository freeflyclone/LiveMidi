/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LogWindow.h"

//==============================================================================
/**
*/
class LiveMidiAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    LiveMidiAudioProcessorEditor (LiveMidiAudioProcessor&);
    ~LiveMidiAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LiveMidiAudioProcessor& audioProcessor;

    // During development (while I'm still learning JUCE semantics), it's useful 
    // to have on-screen diagnostic logging available. Placed here for widest possible
    // availability, without being a static global.
    std::unique_ptr<LogWindow> mLog;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LiveMidiAudioProcessorEditor)
};
