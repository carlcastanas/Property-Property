/*
    Description: This is a collection of functions necessary for proper input handling
    Author: Aaron Nicholas Lizardo Gumapac
*/

#include "../libdefs/InputTools.h"

/*
    This function returns a valid input given a set of desired inputs and their number
    Preconditions: validInputs[] is an array of length > 0 and elements is > 0
    @param validInputs[] an array container of accepted inputs
    @param elements how many accepted inputs there are
*/
char handleInput(char validInputs[], int elements)
{
    //This function returns a validInput given any user input
    char cInitInput = ' ';

    setGreen
        printf("\nInput: ");
    resetColor

    scanf(" %c",&cInitInput);
    while ((getchar()) != '\n');
    
    if(isalpha(cInitInput))                  // check if input requires capitalization
        cInitInput = toupper(cInitInput);    // capitalize

    for (int i = 0; i < elements; i++)
    {
        if(cInitInput != validInputs[i])    // check if input is a member of valid inputs
            continue;                       // continue with loop
        else
            return cInitInput;              // if input is a member of valid inputs, return the input
    }

    setRed
        printf("\ninvalid input, try again\n"); // if input is not a member of valid inputs, prompt a retry
    resetColor

    return handleInput(validInputs,elements);   // recurse 
}