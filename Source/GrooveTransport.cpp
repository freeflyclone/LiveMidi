/*
  ==============================================================================

    GrooveTransport.cpp
    Created: 6 Sep 2025 10:29:26am
    Author:  evan

  ==============================================================================
*/

#include "GrooveTransport.h"

Optional<AudioPlayHead::PositionInfo> GrooveTransport::getPosition() const {
    return mPositionInfo;
}