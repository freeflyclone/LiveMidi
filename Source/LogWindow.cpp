/*
  ==============================================================================

    LogWindow.cpp
    Created: 10 Jul 2025 9:25:31am
    Author:  evan

  ==============================================================================
*/

#include "LogWindow.h"

LogWindow::LogWindow()
{
    // Add other components to your window content
    addAndMakeVisible (myButton);
    myButton.setButtonText ("Click Me!");
    myButton.setBounds (10, 10, 100, 30); 
}

void LogWindow::resized()
{
    // Layout your components here
    myButton.setBounds (10, 10, 100, 30); 
}

