/*
    Description: uiFX.h contains forward definitions for functions that are purely used for UI operations
    Author: Aaron Nicholas Gumapac
*/

#ifndef UIFX_H
#define UIFX_H

#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>   // for nanosleep
#else
#include <unistd.h> // for usleep
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../typedefs/gameTypes.h"
#include "../typedefs/evalTypes.h"
#include "../libdefs/NumTools.h"


// predefined macro that is used to clear the buffer in order to avoid unwanted infinite loops with input processing
#define clearbuff               \
    while ((getchar()) != '\n') \
        ;
// shorthand for system clear
#define clear system("clear"); 
// shorthand for printing newlines, useful for ui
#define newL printf("\n"); 

// COLOR TOOLS

#define resetColor printf("\033[0m"); // resets text colors to default
#define setRed printf("\033[0;31m"); // sets text color to red
#define setGreen printf("\033[0;32m"); // sets text color to green
#define setPurple printf("\033[0;35m"); // sets text color to purple
#define setYellow printf("\033[0;33m"); // sets text color to yellow
#define setCyan printf("\033[0;36m"); // sets the text color to cyan
#define setWhite printf("\033[0;37m"); // sets the text color to white

// performs a pauses the system by millliseconds

void sleep_ms(int milliseconds);

// prints a 2 dimensional array or img

void print2d(char* img[], size_t img_height);

// prints a string sequentially

void print1d(char str[], int strLength, int paceFloor, int paceCeil);

// returns a divider

char* createDivider(char divSymbol, int divLength);

// displays where the player currently is given their position on the board

void displayPos(int pos);

// returns the name of the property given its position on the board for all valid properties

char* getPropertyName(int propIndex);

// shows the balance update that is shown after every turn

void showBalanceUpdate(
                    int p1CurrentBalance,
                    int p1NewBalance,
                    char* p1Name,
                    int p2CurrentBalance,
                    int p2NewBalance,
                    char* p2Name
                    );
                
// shows a short balance update

void showPersonalBalanceUpdate(int currentBalance, int newBalance);

// contextual ending screen that cognratulates the winner(s) according to their win conditions

void displayEndingScreen(struct winstate win, Player p1, Player p2);

// asks the user to press enter in order to continue with the program

void continuePrompt();

// show intro scene

void introScene(int scene);

// display graphics according to pos

void displaySwitch(int pos);

// displays player's pending balance

void showPendingBalance(int pendingBalance);

#endif
