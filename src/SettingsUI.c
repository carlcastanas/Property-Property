/*
    Description: A set of functions used to display the configuration specifications of the settings struct
    Author: Aaron Nicholas Gumapac
*/

#include "../libdefs/SettingsUI.h"

/*
    This function is used to determine whether the game must evaluate multiple wintoggles or not
    Preconditions: toggle1 and toggle2 are valid wintoggle enums
    @param toggle1 enum of type wintoggle defined in evalTypes.h
    @param toggle2 enum of type wintoggle defined in evalTypes.h
    @return a truthy or falsy statement stating whether there are multiple wintoggles to be evaluated or not
*/
bool checkIfMulti(enum wintoggles toggle1, enum wintoggles toggle2)
{
    return toggle1 != DISABLED && toggle2 != DISABLED;
}

/*
    This method is used to display the current configurations set in struct settings
    Preconditions: settingsParam is a valid settings variable with values set
    @param settingsParam settings variable that contains game configurations
*/
void displayCurrentConfig(settings settingsParam)
{

    setYellow
        displayConditions(settingsParam.winsettings); // display current win conditions set
    setCyan
        printf("\n[CURRENT SETTINGS]\n");
        printf(">Renovation cost: %d\n", settingsParam.renovationCost);
        printf(">Railroad rent: %d\n", settingsParam.railRent);
        printf(">Railroad purchase cost: %d\n", settingsParam.railCost);
        printf(">Electric company multiplier: %d\n", settingsParam.electricMulti);
        printf(">Electric company purchase cost: %d\n", settingsParam.electricCost);
    newL
        printf(">Feelin' lucky range\n>>bonus: [%d,%d]\n>>penalty: [%d,%d]\n",
           settingsParam.bonusrange.min, settingsParam.bonusrange.max,
           settingsParam.penaltyrange.min, settingsParam.penaltyrange.max);
    newL
        printf(">Dice faces: %d\n", settingsParam.dicerange.max);
        printf(">Go! Tile bonus: %d\n", settingsParam.goBonus);
        printf(">Go! Passing bonus: %d\n", settingsParam.passingGo);
    newL
        printf(">Starting balance: %d\n", settingsParam.startingBalance);
        printf(">Starting position: %d\n", settingsParam.startingPos);
    resetColor

    printf("\n");
}

/*
    This method is used to display curent win conditions set in struct winconditions
    Preconditions: winconditions is a valid winconditions variable with values set
    @param wincond winconditions variable that contains data that decides game evaluation conditions
*/
void displayConditions(struct winconditions wincond)
{
    bool isMulti = checkIfMulti(wincond.arrWintoggles[0], wincond.arrWintoggles[1]);

    char *defaultBtn = "ACTIVE";                 // default state of default win conditions
    char *context[2] = {defaultBtn, defaultBtn}; // store buttons in a string array in order to dynamically update the UI

    if (wincond.arrWintoggles[0] == DISABLED)    //if these toggles are disabled, update the context
        context[0] = "INACTIVE";
    if (wincond.arrWintoggles[1] == DISABLED)
        context[1] = "INACTIVE";

    printf("\n[WIN CONDITIONS]\n");
    printf("Enemy runs out of properties and falls into bankruptcy: %s (default)\n", defaultBtn);
    printf("Enemy reaches losing balance: %s | [VALUE: %d]\n", context[0], wincond.losingBalance);
    printf("Player reaches winning balance: %s | [VALUE: %d]\n", context[1], wincond.winningBalance);

    if (isMulti)
    {
        char *simulStatus = "FALSE";

        if (wincond.isSimul)
            simulStatus = "TRUE";

        printf("\nAll conditions must be satisfied: %s\n", simulStatus);
    }
}

/* 
    This method displays a dynamic menu used to configure winconditions on the settings screen
    Preconditions: cond, isMulti, isSimul are valid variables that contain non trivial values
    @param wincond winconditions variable that contains data that decides game evaluation conditions
*/
void displayWinconditionsMenu(struct winconditions wincond)
{
    clear

    // check whether the game has to evaluate multiple wintoggles
    bool isMulti = checkIfMulti(wincond.arrWintoggles[0], wincond.arrWintoggles[1]);

    //check whether multiple wintoggles must be satisfied
    bool isSimul = wincond.isSimul;

    displayConditions(wincond); // display current winconditions set

    // three buttons will be used in this menu: set as enable by default
    char *buttons[3] = {"Enable", "Enable", "Disable"};

    /* determine whether the user needs to disable wintoggles */
    if (wincond.arrWintoggles[0] == LOSING_BALANCE_REACHED)
        buttons[0] = "Disable";
    if (wincond.arrWintoggles[1] == WINNING_BALANCE_REACHED)
        buttons[1] = "Disable";
    
    newL
    printf("[1] %s losing balance \n", buttons[0]);
    printf("[2] %s winning balance \n", buttons[1]);

    /* show dynamic menu that changes according to context */
    if (strcmp(buttons[0], "Enable"))
    {
        newL
        printf("\n[3] Edit losing balance \n");
        printf("[LOSING BALANCE: %d]\n", wincond.losingBalance);
    }
    if (strcmp(buttons[1], "Enable"))
    {
        printf("\n[4] Edit winning balance\n");
        printf("[WINNING BALANCE: %d]\n", wincond.winningBalance);
        newL
    }
    if (!isSimul)
        buttons[2] = "Enable";
    if (isMulti)
        printf("[E] %s multi-condition win\n", buttons[2]);

    setGreen
        printf("[S] Save and exit\n");
    resetColor
}
