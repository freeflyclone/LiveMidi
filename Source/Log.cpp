/*
  ==============================================================================

    Log.cpp
    Created: 13 Jul 2025 12:00:52pm
    Author:  evan

  ==============================================================================
*/
#include "Log.h"

void log(const std::string& msg)
{
    std::string outString("LiveMidi: " + msg + "\n");

    OutputDebugString(outString.c_str());
}
