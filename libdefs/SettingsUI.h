/*
    Description: SettingsUI.h is a header file containing necessary definitions for UI methods used in SettingsUI.c 
    Author: Aaron Nicholas Gumapac
*/
#ifndef SETTINGSUI_H
#define SETTINGSUI_H
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../typedefs/evalTypes.h"
#include "../typedefs/stateTypes.h"
#include "../typedefs/numTypes.h"
#include "../libdefs/uiFX.h"


// displays all parameters defined in settings struct relevant to game events

void displayCurrentConfig(settings settingsParam);

// displays all active winconditions

void displayConditions(struct winconditions wincond);

// displays the menu that allows the user to edit winconditions

void displayWinconditionsMenu(struct winconditions wincond);

// checks if multiple conditions must be evaluated

bool checkIfMulti(enum wintoggles toggle1, enum wintoggles toggle2);

#endif