/*
    Description: gameTypes.h is a header file containing necessary definitions for game entities
    Author: Aaron Nicholas Lizardo Gumapac
*/

#pragma once
#ifndef GAMETYPES_H
#define GAMETYPES_H
#include <stdbool.h>

/*
    This structure defines the titular Player.
    //ATTRIBUTES
    name: the player's name
    jailedCounter: how many times the player went to jail
    rentCounter: how many times the player paid rent
    luckyCounter: how many times the player landed on 6 and triggered the Feelin' Lucky event
    pos: the player's position
    balance: player balance
    isJailed: tells whether the player is currently imprisoned or not
    isBankrupt: tells whether the player is currently bankrupt or not
*/
typedef struct Player
{
    unsigned int jailedCounter;
    unsigned int rentCounter;
    unsigned int luckyCounter;
    unsigned int pos;
    int balance;
    char* name;
    bool isJailed;
    bool isBankrupt;
}Player;

#endif