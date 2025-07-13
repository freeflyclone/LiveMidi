/*
  ==============================================================================

    LogWindow.cpp
    Created: 10 Jul 2025 9:25:31am
    Author:  evan

  ==============================================================================
*/

#include "LogWindow.h"

using dw = juce::DocumentWindow;
using jj = juce::Justification;

LogWindow::LogWindow(juce::String name)
    : DocumentWindow(name, juce::Colours::darkgrey, dw::allButtons, true)
{
    // Set up logging window...
    setUsingNativeTitleBar(true);
    setResizable(true, true);
    setBounds(50, 50, 600, 800);
    setVisible(true);
}

LogWindow::~LogWindow() 
{
}

void LogWindow::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(dw::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(juce::FontOptions(15.0f));
    g.drawFittedText("Log window : where's the damn title bar?", getLocalBounds(), jj::centred, 1);
}

void LogWindow::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void LogWindow::closeButtonPressed() 
{
}

