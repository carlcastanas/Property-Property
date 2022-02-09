/* 
    Description: libSettingsEvents.h is a header file for all definitions required for the settings page
    Author: Aaron Nicholas Lizardo Gumapac
*/

#ifndef SETTINGSEVENTS_H
#define SETTINGSEVENTS_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../libdefs/SettingsUI.h"
#include "../libdefs/NumTools.h"
#include "../libdefs/InputTools.h"
//DEFAULT SETTINGS//
#define DEFAULT_ELECTRIC_COST 150
#define DEFAULT_RAILROAD_COST 100
#define DEFAULT_RAILROAD_RENT 35
#define DEFAULT_ELECTRIC_MULTI 8
#define DEFAULT_RENOVATION_COST 50
#define DEFAULT_BONUS_MAX 200
#define DEFAULT_BONUS_MIN 100
#define DEFAULT_PENALTY_MIN 50
#define DEFAULT_PENALTY_MAX 150
#define DEFAULT_WINNING_BALANCE 2000
#define DEFAULT_DICE_MIN 1
#define DEFAULT_DICE_MAX 6
#define DEFAULT_LOSING_BALANCE 0
#define DEFAULT_GO_BONUS 200
#define DEFAULT_PASSING_GO 200
#define DEFAULT_STARTINGBALANCE 200
#define DEFAULT_STARTINGPOS 0


/* INITIALIZATION FUNCTIONS */

settings initializeSettings();
struct winconditions initializeWinconditions();
struct winstate initializeWinstate();

/* Submenus in settings screen */

struct winconditions winconditionsMenu(struct winconditions wincond);
void feelingLuckySubMenu(range *bonusRange, range *penaltyRange);

#endif
