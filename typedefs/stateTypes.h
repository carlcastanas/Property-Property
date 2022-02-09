/*
    Description: stateTypes.h is a header file containing definitions for keeping track of the state of the game
    Author: Aaron Nicholas Lizardo Gumapac
*/
#pragma once
#ifndef STATETYPES_H
#define STATETYPES_H
#include "../typedefs/numTypes.h"
#include "../typedefs/evalTypes.h"

/*
    A structure that contains all settings. Initialized with default values and is further
    customized with the settingsPrompt() function
    //ATTRIBUTES
    winsettings: a winconditions structure that tracks whether the game should continue or not
    electricMulti: the multiplier for the electric company
    railRent: the cost of rent for the railroad
    renovationCost: the cost of renovation
    penaltyrange: the range from which the player will be penalized for rolling a nonprime integer
    bonusrange: the range from which the player will be rewarded for rolling a prime integer
*/
typedef struct settings {
    struct winconditions winsettings;
    int electricMulti;
    int railRent;
    int railCost;
    int electricCost;
    int renovationCost;
    int goBonus;
    int passingGo;
    int startingBalance;
    int startingPos;
    range penaltyrange;
    range bonusrange; 
    range dicerange; 
}settings;

/*
    A structure that tracks the state of the game
    //ATTRIBUTES
    STATEKEY: is a 9 digit integer that tracks all ownerships
    activePlayer: possible values (1 or 2) keeps track of who is currently playing
    settings: is a structure of type settings that is used to determine whether the game should continue or not
*/
extern struct gamestate {
    unsigned int STATEKEY;
    unsigned int activePlayer;
    settings SETTINGS; 
}gamestate;

#endif