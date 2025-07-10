/*
  ==============================================================================

    LogWindow.h
    Created: 10 Jul 2025 9:25:31am
    Author:  evan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class LogWindow : public juce::Component
{
public:
    LogWindow();
    
    void resized() override;

private:
    juce::TextButton myButton;
};
