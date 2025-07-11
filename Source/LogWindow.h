/*
  ==============================================================================

    LogWindow.h
    Created: 10 Jul 2025 9:25:31am
    Author:  evan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

#ifdef WIN32
    #include "Windows.h"
#endif

class LogWindow : public juce::DocumentWindow
{
public:
    LogWindow(juce::String name);
    
    void closeButtonPressed() override;
    void lookAndFeelChanged() override;
    void paint(juce::Graphics& g) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LogWindow)
};
