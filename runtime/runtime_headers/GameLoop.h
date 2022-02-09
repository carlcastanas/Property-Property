/*
    Description: Header file for functions required in the primary game loop
    Author: Aaron Nicholas Gumapac
*/
#pragma once
#ifndef GAMELOOP_H
#define GAMELOOP_H
#include "../../typedefs/gameTypes.h"
#include "../../typedefs/stateTypes.h"
#include "../../libdefs/uiFX.h"
#include "../../libdefs/SettingsEvents.h"
#include "../../libdefs/PlayerEvents.h"
#include "../../libdefs/InputTools.h"

#define STARTING_STATEKEY 444949444
#define STATEKEY_OFFSET -4

// PLAYER DEFAULTS
#define DEFAULT_STARTINGPOS 0
#define DEFAULT_STARTINGBALANCE 200

// gamepkg is a struct of the game as one package (variable) to be passed around as parameters by functions (higher order/pure) that preserves and monitors the current game being played
// contains gamestate and the 2 players necessary to play Property...Property
extern struct gamepkg {
    struct gamestate state; // state of the game
    struct Player* arrPlayerContainer; // an array of type player that contains both players
}gamepkg;

// initialize gamestate

extern struct gamestate initializeGamestate();

// initialize Player

extern Player initializePlayer(settings config);

// calls game events and updates game values

struct gamepkg updateGame(struct gamepkg game);

// updates the values of the player and associated state values

void updatePlayer(unsigned int* ptrActivePlayer, bool* ptrP1Jail, bool* ptrP2Jail);

// display the current game's status 

void showGameStatus(struct gamepkg game);

// updates the winstate of the game given winsettings and the two players

struct winstate updateWinState(winconditions winsettings, Player p1, Player p2);

// checks whether the game should continue or not

bool continueGame(enum winner winState);

// event for when player balance is less than a required payment

#endif