/*
    Header file for Settings.c
    Author: Aaron Nicholas Lizardo Gumapac
*/

#pragma once
#ifndef SETTINGS_H
#define SETTINGS_H
#include "../../typedefs/stateTypes.h"
#include "../../typedefs/gameTypes.h"
#include "../../libdefs/SettingsEvents.h"
#include "../../libdefs/InputTools.h"

// Primary settings screen function

settings settingsPrompt(settings initsettings);
#endif