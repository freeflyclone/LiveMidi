/*
  ==============================================================================

    Log.h
    Created: 13 Jul 2025 12:00:52pm
    Author:  evan

  ==============================================================================
*/
#pragma once

#ifdef WIN32
#include <Windows.h>
#endif

#include <string>

extern void log(const std::string& msg);
