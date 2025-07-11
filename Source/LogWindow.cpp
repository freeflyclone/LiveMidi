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

    // Setup logging...
#ifdef WIN32
    if (AllocConsole())
    {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);

        std::cout << "This is a test to stdout" << std::endl;
        std::cerr << "This is a test to stderr" << std::endl;
    }
#endif
}

void LogWindow::closeButtonPressed()
{
    juce::JUCEApplication::getInstance()->systemRequestedQuit();
}

void LogWindow::lookAndFeelChanged()
{
    setBackgroundColour(findColour(juce::ResizableWindow::backgroundColourId));
}

void LogWindow::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(juce::FontOptions(15.0f));
    g.drawFittedText("Your mom was here.", getLocalBounds(), juce::Justification::centred, 1);

}