/* 
    Description: libPlayerEvents.h is a header file for all functions related to the player
    Author: Aaron Nicholas Lizardo Gumapac
*/
#ifndef PLAYEREVENTS_H
#define PLAYEREVENTS_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../typedefs/gameTypes.h"
#include "../typedefs/numTypes.h"
#include "../libdefs/GameEvents.h"
#include "../libdefs/NumTools.h"
#include "../libdefs/uiFX.h"
// player roll dice event

int rollDice(range dicerange);

// returns a string of all the player's properties

char* getAllPlayerProperties(unsigned int STATEKEY, unsigned int OFFSET, unsigned int playerID);

// checks if the player owns any properties

bool playerOwnsProperties(unsigned int STATEKEY, unsigned int OFFSET, unsigned int playerID);

// a dialogue prompt that decides end turn

bool playerDialogue(char *strDialogueMsg, char *validInputs);

// checks whether the player owns the current property or not

bool playerOwns(unsigned int playerID, int propIndicator);

// displays the player's stats after the game has finished

void displayPlayerEndingStats(Player PLAYER, unsigned playerID, unsigned int STATEKEY);

// returns a valid sell choice given the statekey and the current player's ID

int getPlayerSellChoice(unsigned int STATEKEY, int OFFSET, unsigned int playerID);

// changes playername variable

void fetchPlayerName(char **ptrPlayerName);

#endif
