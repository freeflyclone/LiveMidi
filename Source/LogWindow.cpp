/*
  ==============================================================================

    LogWindow.cpp
    Created: 10 Jul 2025 9:25:31am
    Author:  evan

  ==============================================================================
*/

#include "LogWindow.h"

LogWindow::LogWindow(juce::String name)
    : juce::DocumentWindow(name, juce::Colours::black, DocumentWindow::allButtons)
{
    setSize(600, 900);
    setTopLeftPosition(200, 200);
    setVisible(true);
    setResizable(true, true);
    setBackgroundColour(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void LogWindow::closeButtonPressed()
{
    juce::JUCEApplication::getInstance()->systemRequestedQuit();
}

void LogWindow::lookAndFeelChanged()
{
    setBackgroundColour(findColour(juce::ResizableWindow::backgroundColourId));
}
