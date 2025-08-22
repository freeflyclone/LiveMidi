/*
  ==============================================================================

    GrooveBrowser.h
    Created: 22 Aug 2025 10:37:17am
    Author:  evan

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "GrooveStore.h"

using namespace juce;

class GrooveBrowser : public Component {
public:
    GrooveBrowser();
    ~GrooveBrowser();

    void Initialize(File);

protected:
    GrooveStore store;
};