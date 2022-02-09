/*
    Description: A set of type definitions necessary for evaluating win conditions
    Author: Aaron Nicholas Gumapac
*/

#pragma once
#ifndef EVALTYPES_H
#define EVALTYPES_H
#include <stdbool.h>

// handy syntax-sugar for customizing win conditions in the settings screen
enum wintoggles{ WINNING_BALANCE_REACHED, LOSING_BALANCE_REACHED, DISABLED };

// label for winner
enum winner{ NONE, TIE, PLAYER1, PLAYER2 };

// tells the game how exactly the player won
enum winContext{ ENEMY_BANKRUPTCY, REACHED_WINNING_BALANCE, ENEMY_LOSING_BALANCE, NOCONTEXT };

/*
    tells the game who won and how
    //ATTRIBUTES
    winner: enum that names the winner
    winRationale: list for the reason(s) the player won for 
*/
extern struct winstate {
    enum winner winner; // winner type
    enum winContext* winRationale; // context clues as to how the game was decided
}winstate;

struct winconditions; // forward declaration of wincondition 

/*
    a set of definitions that tells the game whether the game is done or not
    //ATTRIBUTES
    arrwintoggles: describes the conditions that must be satisfied in order to determine a winner
    winstate: contains the winner and how they won
    isSmul: tells you whether both wintoggles must be satisfied
*/
typedef struct winconditions {
    enum wintoggles arrWintoggles[2];
    struct winstate winstate;
    int losingBalance;
    int winningBalance;
    bool isSimul;
}winconditions;

#endif
