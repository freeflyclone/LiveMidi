/*
  ==============================================================================

    GrooveTransport.h
    Created: 6 Sep 2025 10:29:26am
    Author:  evan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using namespace juce;

class GrooveTransport : public AudioPlayHead {
public:
    GrooveTransport() {};
    ~GrooveTransport() {};

    Optional<PositionInfo> getPosition() const;

private:
    PositionInfo mPositionInfo;
};