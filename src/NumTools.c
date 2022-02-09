/*
    Description: Collection of functions that aid in purely numerical operations
    Author: Aaron Nicholas Lizardo Gumapac
*/
#include "../libdefs/NumTools.h"

// clears the buffer in order to avoid unwanted infinite loops
#define clearbuff               \
    while ((getchar()) != '\n') \
        ;


/*
    This function returns true if the given number is within the set range (inclusive) 
    Precondition: num, field.min, and field.max are integers within -2,147,483,648 and 2,147,483,647
    @param num the number to be evaluated
    @param field the range to be evaluated against 
    @returns truthy or falsy value
*/
bool checkIfInRange(int num, range field)
{
    if (num <= field.max && num >= field.min)
        return 1;

    return 0;
}

/*
    This function returns a range after prompting the user to edit its minimum and maximum values
    Preconditions: varRange is a valid range with a min and max value; type is a string with length > 0
    @param varRange the range to be modified
    @param type string that determines what to display on the prompt
    @returns a range with user-defined minima and maxima
*/
range editRange(range varRange, char *type)
{
    clear

    printf("[MIN: %d ----- MAX: %d]\n", varRange.min, varRange.max);
    printf("[W] Edit %s min\n", type);
    printf("[E] Edit %s max\n", type);
    printf("[S] Save and exit\n");
    char subMenuInput[3] = {'W', 'E', 'S'};
    char cSettingsSelect = handleInput(subMenuInput, 3);

    switch (cSettingsSelect)
    {
        case 'W':
            varRange.min = getValidInteger("Enter minimum: ");
            break;
        case 'E':
            varRange.max = getValidInteger("Enter maximum: ");
            break;
        case 'S':
            if (varRange.min >= varRange.max)
            {
                printf("\nERROR: INVALID RANGE\n");
                sleep_ms(1000);
            }
            else
                return varRange;
            
            break;
        default:
            printf("Critical Error, called by: %s", __func__);
            break;
    }

    return editRange(varRange, type);
}

/*
    After prompting the user for an input, this function returns an integer.
    If user input is invalid, it continues to prompt the user for an input
    ad infinitum.
    Preconditions: strMsg is a string of length > 0
    @param strMsg a string of characters used to contextualize the prompt
    @returns an integer
*/
int getValidInteger(char *strMsg)
{
    float tmp;
    int num;
    bool cont;
    printf(strMsg);

    do
    {
        cont = 0;
        if (scanf(" %f", &tmp) != 1)
        {
            setRed
                printf("\nInvalid entry, try again\n");
            resetColor
            cont = 1;
        }

        clearbuff
            num = (int)tmp;
    } 
    while (cont == 1);

    return num;
}

/*
    This method sets a pointer location to null. This is done to imitate smart 
    pointers and ensures that all pointers are only used once.
    Preconditions: ptr is a pointer that points to a valid location in memory
    @param ptr the pointer to be nullified
*/
void freePtr(void **ptr)
{
    free(*ptr);
    *ptr = NULL; // dereference the double pointer in order to set the pointer it points to null
}

/*
    This method changes a the value of an integer variable given its parameter 
    Preconditions:
        parameterPtr points to a valid integer variable 
        strMsg is an array of chars with length > 0
    @param parameterPtr the pointer of the variable to be changed
    @param strMsg the message to be displayed to the user during the prompt
*/
void changeIntParam(int *parameterPtr, char *strMsg)
{
    setGreen
        printf("\n[CURRENT VALUE: %d]\n", *parameterPtr);
    resetColor

    float tmp;
    bool cont;
    printf("%s", strMsg);
    do
    {
        cont = 0;
        if (scanf(" %f", &tmp) != 1)
        { // if user input is an invalid int, employ an infinite loop
            fflush(stdin);
            setRed
                printf("\nInvalid input, try again\n");
            resetColor
            cont = 1;
        }
    } 
    while (cont == 1);

    *parameterPtr = (int)tmp;
}

/*
    This method changes a the value of a float variable given its parameter 
    Preconditions:
        parameterPtr points to a valid float variable 
        strMsg is an array of chars with length > 0
    @param parameterPtr the pointer of the variable to be changed
    @param strMsg the message to be displayed to the user during the prompt
*/
void changeFloatParam(float *parameterPtr, char *strMsg)
{
    setGreen
        printf("\n[CURRENT VALUE: %.2f]\n", *parameterPtr);
    resetColor

    float tmp;
    bool cont;
    printf("%s", strMsg);
    do
    {
        cont = 0;

        if (scanf("%f", &tmp) != 1)
        { // if user input is an invalid float, employ an infinite loop
            printf("\nInvalid input, try again\n");
            cont = 1;
        }
    } 
    while (cont == 1);

    *parameterPtr = tmp;
}

/*
    This function, after comparing two numerical values, returns the greater value 
    Precondition: n1 and n2 are numerical values
    @param n1 the first number to be evaluated
    @param n2 the second number to be evalated
    @returns the greater value
*/
float getHigherVal(float n1, float n2)
{
    if (n1 > n2)
        return n1;
    else if (n2 > n1)
        return n2;

    printf("values are equal");
    return 0; // standard error code
}

/*
    A rudimentary function that raises a base to a power, does not cover negative bases/powers
    Preconditions: base is nonnegative, power is nonnegative
    @param base the number to be raised
    @param power how much to raise that base
    @returns the integer value equivalent to the base's exponentiation
*/
int exponentiateNum(int base, int power)
{
    int num = 1; // base case

    if (power == 0)
    {
        return num;
    }

    for (size_t i = power; i > 0; i--)
    {
        num *= base; // base does not change, num keeps being multiplied
    }

    return num;
}

/*
    A function that returns a random number given a range
    Preconditions: ceil > floor
    @param floor the minima of the range
    @param ceil the maxima of the range
    @returns a random integer within a given range (inclusive)
*/
int getRandNum(int floor, int ceil)
{
    return (
        floor + ((rand() % ceil) - floor + 1));
}

/*
    A function that sets every number within the given index to 0
    @Preconditions: index is nonnegative, num is >= 1
    @param num the number to be normalized
    @param index the index from which the normalization begins
    @returns an integer that has been normalized
*/
int normalizeNumByIndex(int num, int index)
{ //index starts at 0 and is ordered from right to left
    return (
        (num / exponentiateNum(10, index)) // delimit num by index
        * exponentiateNum(10, index));     // set every value to zero
}

/*
    Rudimentary primality checking function that determines whether the given number is prime or not
    @param num the number to be evaluated
    @returns a truthy or falsy statement determined by the primality of the given number
*/
bool isPrime(int num)
{
    unsigned int flag = 0;   // used to track how many times the number has been divided without a remainder

    for (size_t i = 1; i <= num; i++)
    {
        if (num % i == 0)
            flag += 1;
    }

    return (flag == 2);     // true if 2 divisors, false otherwise
}

/*
    Simple function that counts how many digits a number has
    @param num the number whose digits must be counted
    @returns the number of digits within num
*/
int getDigits(int num)
{
    int counter = 0;
    while(num > 0)
    {
        num /= 10;
        counter++;
    }
    return counter;
}
