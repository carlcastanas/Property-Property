/*
    Description: NumTools.h is the header file for all independent numerical functions used in the program
    Author: Aaron Nicholas Gumapac
*/
#ifndef NUMTOOLS_H
#define NUMTOOLS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../typedefs/numTypes.h"
#include "../libdefs/uiFX.h"
#include "../libdefs/InputTools.h"

// helper function that frees and nullifies pointers

void freePtr(void** ptr);

// allows you to edit a range

range editRange(range varRange, char* type);

// prompts and returns a valid integer
 
int getValidInteger(char* strMsg);

// changes a float parameter 

void changeFloatParam(float* parameterPtr, char* strMsg);

// changes an int parameter 

void changeIntParam(int* parameterPtr, char* strMsg);

// raises base to a power

int exponentiateNum(int base, int power);

// checks if a given number is within a given range

bool checkIfInRange(int num, range field);

// gives you the higher value in a numerical comparison

float getHigherVal(float n1, float n2);

// returns true if the given number is a prime, else, returns false

bool isPrime(int num);

// sets every number within index to 0

int normalizeNumByIndex(int num, int index); 

// gives you a random number between floor and ceil

int getRandNum(int floor, int ceil);

// counts how many digits a number has

int getDigits(int num);

#endif
