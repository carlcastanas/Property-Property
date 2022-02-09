/*
    Description: Header file for functions integral for game event processing.
    Author: Aaron Nicholas Gumapac
*/

#pragma once
#ifndef GAMEEVENTS_H
#define GAMEEVENTS_H

#include "../typedefs/stateTypes.h"
#include "../typedefs/gameTypes.h"
#include "../libdefs/NumTools.h"
#include "../libdefs/PlayerEvents.h"


// returns the integer at index

int readStatekeyAtIndex(unsigned int STATEKEY, unsigned int index, int OFFSET);

// changes the statekey with value at index

int mutateStatekeyAtIndex(unsigned int STATEKEY, unsigned int index, unsigned int value, int OFFSET);

// returns the cost of the property purchase

int getPropertyCost(int propIndex, int electricCost, int railCost);

// returns the cost of rent for the property

int getRent(int propIndex, int roll, int electricMulti, int railRent);

// function for when the player goes into debt 

unsigned int sellPropertyEvent(bool* ptrIsBankrupt, settings config, int STATEKEY,
                                int STATEKEY_OFFSET, int currentPlayerKey, 
                                int requiredPayment, int* currentBalance);

// saves the game
struct gamepkg saveGame(Player currentPlayer, int currentPlayerKey,
                        Player opposingPlayer, int enemyPlayerKey, 
                        struct gamestate containedstate);

#endif