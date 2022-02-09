/*
    Description: InputTools.h is the header file for functions used purely for handling user input
    Author: Aaron Nicholas Gumapac
*/

#pragma once
#ifndef INPUTTOOLS_H
#define INPUTTOOLS_H

#include "../libdefs/uiFX.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>


// gives you a valid char given a set of valid inputs

char handleInput(char validInputs[], int elements);

#endif