/*
  ==============================================================================

    LogWindow.h
    Created: 10 Jul 2025 9:25:31am
    Author:  evan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class LogWindow : public juce::DocumentWindow
{
public:
    LogWindow(juce::String name);
    ~LogWindow();

    void paint(juce::Graphics& g);
    void resized() override;
    void closeButtonPressed() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LogWindow)
};
