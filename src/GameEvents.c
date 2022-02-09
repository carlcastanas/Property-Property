/*
    Description: GameEvents.c is a collection of functions that are required to "play" the game
    Author: Aaron Nicholas Lizardo Gumapac
*/

#include "../libdefs/GameEvents.h"

/*
    Dynamically calculates the cost necessary to pay rent when the player lands on a property owned by the opponent
    Preconditions: the property being checked is owned by the opponent
    @param propIndex the position of the property on the board
    @param roll the player's dice roll during this turn
    @param electricMulti the electric company's multiplier, described in struct settings
    @param railRent the cost of rent for the railroad
    @returns the cost of rent for the property at the given index
*/
int getRent(int propIndex, int roll, int electricMulti, int railRent)
{
    if (propIndex == 2)
        return electricMulti * roll;
    if (propIndex == 7)
        return railRent;

    return propIndex % 7 * 20 * 0.2;
}

/*
    Dynamically calculates the cost necessary to purchase a property owned by the bank
    Preconditions: the property being checked is owned by the bank
    @param propIndex the position of the property on the board
    @param electricCost the cost necessary to purchase the electric company, described in struct settings
    @param railCost the cost necessary to purchase the railraod, described in struct settings
    @returns the cost of the property at the index
*/
int getPropertyCost(int propIndex, int electricCost, int railCost)
{
    if (propIndex == 2)
        return electricCost;
    if (propIndex == 7)
        return railCost;

    return propIndex % 7 * 20;
}

/*
    This pure function creates and returns a new mutated statekey. The mutation occurs at the given index for one digit.
    Preconditions: STATEKEY is a 9 digit integer
    @param STATEKEY 9 digit integer used to track property statuses
    @param index the position of the digit to be changed
    @param value the value of the mutation
    @param OFFSET predefined statekey offset
    @returns new statekey with value inserted at index
*/
int mutateStatekeyAtIndex(unsigned int STATEKEY, unsigned int index, unsigned int value, int OFFSET)
{
    if (STATEKEY / exponentiateNum(10, index - 1) == 0 || index < 1)
    { // if the given index is outside of the statekey's range

        setRed
            printf("\ninvalid index");
        resetColor

        return 0; // standard error value
    }

    index -= 1;
    value %= 10;                                                   // normalize value to prevent inputs > 1 digit
    int normalizedNum = normalizeNumByIndex(STATEKEY, index + 1);  // set values inclusive of index to zero
    int insertion = (value - OFFSET) * exponentiateNum(10, index); // insert the mutation by the index's position
    int trailing = STATEKEY % exponentiateNum(10, index);          // add trailing unmutated numbers
    int mutatedStateKey = normalizedNum + insertion + trailing;    // final summation

    return mutatedStateKey;
}

/*
    This function returns the value of the statekey at the given index
    Preconditions: index is between 1 and 9
    @param STATEKEY 9 digit integer that tracks all properties on the board
    @param index the location of the digit to be returned
    @OFFSET predefined statekey offset
    @returns digit at the index
*/
int readStatekeyAtIndex(unsigned int STATEKEY, unsigned int index, int OFFSET)
{

    if (STATEKEY / exponentiateNum(10, index - 1) == 0 || index < 1)
    { // if the given index is outside of the statekey's range

        setRed
            printf("\ninvalid index");
        resetColor

        return 0; // standard error value
    }

    return (((STATEKEY / exponentiateNum(10, index - 1)) % 10) + OFFSET);
}

/*
    This function changes player bankruptcy status depending on the player's ability to pay their payment
    @param ptrIsBankrupt pointer variable for player's bankruptcy status
    @param STATEKEY the game's current STATEKEY (property tracker)
    @param STATEKEY_OFFSET offest or hashing key required to read the statekey
    @param requiredPayment the balance the player has to settle
    @param ptrPlayerBalance pointer variable for the player's current balance
    @param config settings variable necessary for calculating the cost of properties
*/
unsigned int sellPropertyEvent(bool* ptrIsBankrupt, settings config, int STATEKEY,
                                int STATEKEY_OFFSET, int currentPlayerKey, 
                                int requiredPayment, int* ptrPlayerBalance)
{

    // continue displaying the prompt while the player does not have enough money to pay rent
    bool playerCanSell = playerOwnsProperties(STATEKEY,STATEKEY_OFFSET,currentPlayerKey); 

    if(playerCanSell)
    {
        char* wumpus = "\n🐋Wumpus: HELLOW IM WUMPUS THE WHALE AND YOU'RE WATCHING\n";
        char* showTitle = "\n---->\"How to Sell Your Assets for A Massive Loss!\"<----\n";
        char* sucker = "\nWatch this sucker squander his houses away in a spree of panic sellling!\n";
        print1d(wumpus, strlen(wumpus), 100, 100);
        print1d(showTitle, strlen(showTitle), 200, 200);
        print1d(sucker, strlen(sucker), 120, 120);
        sleep_ms(500);
    }
    while(*ptrIsBankrupt && playerCanSell) // check if player still has remaining properties to sell    
    {
    

        if(playerCanSell) // if you can sell enough of your properties, the bank might rethink 😏  
        {
            printf("[DEBTS: 💲%d]\n",requiredPayment);  // display requiredpayment
            for (size_t i = 1; i <= 9; i++)             // loop and read all properties on the statekey
            {
                int propID = readStatekeyAtIndex(STATEKEY, i, STATEKEY_OFFSET);
                        
                if(playerOwns(currentPlayerKey,propID)) // display the property name and cost if player owns 
                {
                    char* strPropName = getPropertyName(i);
                    int propertyCost = getPropertyCost(i, config.electricCost,
                                                        config.railCost) * 0.5;

                    printf("[%d]: %s %d$\n",(int)i, strPropName, propertyCost);
                }
            }
            printf("[WALLET: 💲%d\n",*ptrPlayerBalance);
            
            // which properties the player would like to sell
            int toBeSold = getPlayerSellChoice(STATEKEY, STATEKEY_OFFSET,
                                               currentPlayerKey);
            STATEKEY = mutateStatekeyAtIndex(
                        STATEKEY, toBeSold,
                        0, STATEKEY_OFFSET);                                // reset the value of the property at 0, relinquishing it to the bank

            int sellPrice = getPropertyCost(toBeSold, config.electricCost, // sell cost is half of the original cost
                                            config.railCost) * 0.5; 

            setCyan
                printf("\n%s 🐳 SOLD FOR: %d\n",getPropertyName(toBeSold),sellPrice);
            resetColor

            showPersonalBalanceUpdate(*ptrPlayerBalance, *ptrPlayerBalance + sellPrice);
            *ptrPlayerBalance += sellPrice;                                   // reimburse the player
            continuePrompt();

            if(*ptrPlayerBalance >= requiredPayment)                         // check if player is able to pay required amount
            {
                *ptrIsBankrupt = false;

                setGreen
                    printf("\n🐋Wumpus: You now have enough capital to escape your quarry!\n");
                resetColor

                sleep_ms(500);
                printf("\n[Press ENTER to pay your debts]");
                getchar();
            }
        }
        playerCanSell = playerOwnsProperties(STATEKEY,STATEKEY_OFFSET,currentPlayerKey); 
    }
    return STATEKEY;
}
