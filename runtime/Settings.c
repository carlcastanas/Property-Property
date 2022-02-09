/*
    Description: Contains the function necessary for game configuration
    Author: Aaron Nicholas Gumapac
*/

#include "runtime_headers/Settings.h"

/*
    Primary settings menu function that enables customization. Calls functions defined in "Settings.h".
    @param initsettings settings struct with initialized values
*/
settings settingsPrompt(settings initsettings)
{
    char cSettingsSelect;

    do
    { // while the player has yet to press 'G', continue displaying the settings screen
        clear
        displayCurrentConfig(initsettings);        // defined in SettingsUI.c, used to display current settings
        
        char* div = createDivider('=',23);
        printf("%s[SETTINGS MENU]%s\n\n",div,div);
        printf("[1] Edit win conditions\n");    
        printf("[2] Edit renovation cost\n");   
        printf("[3] Edit railroad rent\n");     
        printf("[4] Edit railroad purchase cost\n");                
        printf("[5] Edit the electric company's multiplier\n");
        printf("[6] Edit the electric company's purchase cost\n");
        
        newL
          
        printf("[7] Edit feeling lucky range\n");
        printf("[8] Edit dice faces\n");
        printf("[9] Edit Go! tile bonus amount\n");
        printf("[0] Edit Go! passing bonus amount\n");

        newL

        printf("[X] Edit starting balance\n");
        printf("[F] Edit starting position\n");

        newL

        setRed
            printf("[D] Reset settings\n");     // select to call initializeSettings() again
        resetColor

        setGreen
            printf("[S] Save and Exit \n\n");   // select to exit the settings prompt and store modifications made
        resetColor

        char validSettingsInput[] = "1234567890DSXF";
        cSettingsSelect = handleInput(validSettingsInput, strlen(validSettingsInput));

        switch (cSettingsSelect)
        {
            case '1':
                initsettings.winsettings = winconditionsMenu(initsettings.winsettings);
                break;
            case '2':
                printf("\nHow much money it would cost to renovate a property\n");
                changeIntParam(&initsettings.renovationCost, "Enter renovation cost: ");
                break;
            case '3':
                printf("\nHow much money you would have to fork over when you're paying rent for the RailRoad\n");
                changeIntParam(&initsettings.railRent, "Enter railroad rent: ");
                break;
            case '4':
                printf("\nSelf explanatory.\n");
                changeIntParam(&initsettings.railCost, "Enter railroad purchase cost: ");
                break;
            case '5':
                printf("\nBy how much should your roll be multiplied when paying rent in the Electric Company.\n");
                changeIntParam(&initsettings.electricMulti, "Enter electric co. multiplier: ");
                break;
            case '6':
                printf("\nDuh.\n");
                changeIntParam(&initsettings.electricCost, "Enter electric co. purchase cost: ");
                break;
            case '7':
                printf("\nHow much you lose/gain when you roll a nonprime/prime number when talking to the witch\n");
                sleep_ms(500);
                continuePrompt();
                feelingLuckySubMenu(
                    &initsettings.bonusrange,
                    &initsettings.penaltyrange);
                break;
            case '8':
                printf("\nThis defines the die's maximum value\n");
                changeIntParam(&initsettings.dicerange.max, "How many faces should the dice have (6 default) ?: ");
                break;
            case '9':
                printf("\nGo! tile bonus is the amount of cash players get for landing on Go! and simply not passing by it.\n");
                changeIntParam(&initsettings.goBonus, "Enter Go! tile bonus amount: ");
                break;
            case '0':
                printf("\nPassing go! amount alludes to the amount of cash the players get each time they pass by Go!\n");
                changeIntParam(&initsettings.passingGo, "Enter passing Go! bonus amount: ");
                break;
            case 'X':
                printf("\nHow much money the two players start with\n");
                changeIntParam(&initsettings.startingBalance, "Enter starting balance: ");
                break;
            case 'F':
                printf("\nWhere you begin on the board\n");
                changeIntParam(&initsettings.startingPos, "Enter starting position: ");
                break;
            case 'D':
                initsettings = initializeSettings();
            default:
                break;
        }
    } 
    while (cSettingsSelect != 'S');

    setGreen
        printf("\nConfig Saved!\n\n");
    resetColor

    return initsettings;
}
