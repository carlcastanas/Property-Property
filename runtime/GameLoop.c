/*
    Description: A collection of functions concerned only with the primary game loop
    Author: Aaron Nicholas Gumapac
*/

#include "runtime_headers/GameLoop.h"

/*
    Creates a new player based on configuration settings
    @returns player with initial values
*/
Player initializePlayer(settings config)
{
    Player initPlayer;

    initPlayer.pos = config.startingPos;
    initPlayer.balance = config.startingBalance;
    initPlayer.jailedCounter = 0;
    initPlayer.luckyCounter = 0;
    initPlayer.rentCounter = 0;
    initPlayer.name = malloc (256);
    initPlayer.isBankrupt = false;
    initPlayer.isJailed = false;

    return initPlayer;
}

/*
    Initializes gamestate with default values 
    @returns initial gamestate
*/
struct gamestate initializeGamestate()
{
    struct gamestate initgamestate;
    initgamestate.activePlayer = 0;
    initgamestate.SETTINGS = initializeSettings();
    initgamestate.STATEKEY = STARTING_STATEKEY;

    return initgamestate;
}

/*
    Determines whether the game should continue or not given an enum winner
    @param WINNER enum that tells the game whether a winner has been decided
    @returns boolean value that dictates the continuation of the game
*/
bool continueGame(enum winner WINNER)
{
    if(WINNER != NONE)
        return false;

    return true;
}

/*
    A method that accesses and modifies the state's activePlayer and both players' jail status
    @param ptrActivePlayer the pointer variable pointing to the current active player as described by the state variable
    @param ptrP1Jail pointer to jail status of player 1
    @param ptrP2Jail pointer to jail status of player 2
*/
void updatePlayer(unsigned int* ptrActivePlayer, bool* ptrP1Jail, bool* ptrP2Jail)
{
    int activePlayer = *ptrActivePlayer; // dereference activePlayer pointer
    
    if(activePlayer == 1)
    {
        if(*ptrP2Jail)
        {
            *ptrP2Jail = false;

            if(*ptrP1Jail)
                *ptrActivePlayer = 3;
        }
        else if(!*ptrP2Jail)
            *ptrActivePlayer = 2;
    }
    if(activePlayer == 2)
    {
        if(*ptrP1Jail)
        {
            *ptrP1Jail = false;

            if(*ptrP2Jail)
                *ptrActivePlayer = 4;
        }
        else if(!*ptrP1Jail)
            *ptrActivePlayer = 1;
    }
}

/*
    Updates player position and dynamically draws a route
    @param player the player's whose position is being updated
    @param currentPos the position the player is moving from
    @param newPos destination position
    @param passingGoBonus how much money the bank will give you if you pass by the Go tile
*/
Player updatePlayerPosition(int currentPos, int newPos, int passingGoBonus, Player player)
{
    int i = currentPos;

    for(;i <= newPos; i++)
    {
        for(int k = currentPos; k < i;k++)
        {
            setYellow

            if(k% 10 == 4) // indicate jail time 
                setRed
            if(k % 10 == 6) // indicate lucky position
                setPurple  
            if(k % 10 == 0) // indicate go position
                setCyan
            
            printf("%d ",k % 10);
            sleep_ms(50);
            fflush(stdout);
        }

        setGreen
            printf("%d",i%10);
        resetColor

        fflush(stdout);

        if(i != newPos)
            printf("\r");

        fflush(stdout);
        sleep_ms(500);
    }
    
    sleep_ms(300);

    if(newPos > 10 && newPos % 10 != 0)
    {
        setGreen
            printf("\nYou passed by Go! Here's %d\n",passingGoBonus);
        resetColor

        player.balance += passingGoBonus;
    }

    player.pos = newPos%10;
    return player;
}

/*
    This function returns a gamepkg with updated winsettings values
    @param currentPlayer the player whose turn it is
    @param currentPlayerKey currentPlayer's location (index) in the player array
    @param opposingPlayer currentPlayer's enemy
    @param enemyPlayeryKey opposingPlayer's location (index) in  the player array
    @param lstate the state evaluated during updateGame()
    @returns updated gamepkg struct with new winsettings values
*/
struct gamepkg saveGame(Player currentPlayer, int currentPlayerKey, Player opposingPlayer, int enemyPlayerKey, struct gamestate lstate)
{
    Player* playerContainer = malloc (512);
    playerContainer[currentPlayerKey - 1] = currentPlayer;
    playerContainer[enemyPlayerKey - 1] = opposingPlayer;
    struct gamestate state = lstate;
    state.SETTINGS.winsettings.winstate = updateWinState(state.SETTINGS.winsettings, playerContainer[0], playerContainer[1]); // evaluate win settings

    struct gamepkg updatedGame;
    updatedGame.state = state;
    updatedGame.arrPlayerContainer = playerContainer;
    
    return updatedGame;
}

/*
    Updates game data depending on player actions 
    @param game game package containing all game data
    @returns updated game after 1 game turn
*/
struct gamepkg updateGame(struct gamepkg game)
{
    fflush(stdout);

    if(game.state.activePlayer == 3 || game.state.activePlayer == 4)
    {
        setRed
            printf("\nBOTH PLAYERS HAVE BEEN IMPRISONED\n");
        resetColor

        game.state.activePlayer -= 2;
        return game;
    }

    showGameStatus(game);
    
    struct gamepkg updatedGame = game;       // localize game package
    struct gamestate lstate = game.state;    // localize gamestate
    settings config = game.state.SETTINGS;   // localize settings and create shorthand for code readability

    Player* playerContainer = game.arrPlayerContainer;              // localize player container

    unsigned int currentPlayerKey = lstate.activePlayer;            // integer value used to index currentPlayer
    unsigned int enemyPlayerKey = currentPlayerKey == 1 ? 2 : 1;    // integer value used to index enemy player

    Player currentPlayer = playerContainer[currentPlayerKey - 1];   // current player from player container
    Player opposingPlayer = playerContainer[enemyPlayerKey - 1];    // opposing player from player container

    // Evaluate Player Position
    printf("\n[Press ENTER to roll the dice]\n");
    getchar();
    char dots[] = "...";
    print1d(dots, strlen(dots), 80,80);
    unsigned int roll = rollDice(config.dicerange);
    printf("\nThe dice says: %d!\n", roll);
    sleep_ms(1000);

    // update player positiion
    currentPlayer = updatePlayerPosition(currentPlayer.pos,
    currentPlayer.pos + roll, config.passingGo, currentPlayer);
    updatedGame.arrPlayerContainer[currentPlayerKey - 1] = currentPlayer;
    continuePrompt();

    int pendingOpponentBalance = opposingPlayer.balance;    // player 2 balance to be sent after updateGame() events
    int pendingPlayerBalance = currentPlayer.balance;       // player 1 balance to be sent after updateGame() events

    // store player position for easier syntax
    unsigned int pos = currentPlayer.pos;

    clear

    showGameStatus(updatedGame);    // show updated game status after clearing the screen
    bool isHouse = true;            // default property type
    displaySwitch(pos);             // display appropriate game dialogue for the current position
    
    // instantiate localized statekey
    unsigned int STATEKEY = lstate.STATEKEY;
    switch(pos)
    {
        case 0:         // player lands on Go!
        {
            showPersonalBalanceUpdate(pendingPlayerBalance, pendingPlayerBalance + config.goBonus);
            pendingPlayerBalance += config.goBonus;
            continuePrompt();
            break;
        }
        case 4:         // player is Jailed :(
        {
            currentPlayer.isJailed = true;
            currentPlayer.jailedCounter += 1;
            continuePrompt();
            break;  
        }
        case 6:         // player lands on feelin' lucky plot
        {
            currentPlayer.luckyCounter += 1;
            printf("\n[Press ENTER to Test Your Luck]\n");
            getchar();
            char* strDivining = "divining your luck...\n";
            print1d(strDivining, strlen(strDivining), 150, 150);
            int num = rollDice(config.dicerange);
            sleep_ms(500);

            if(num == 1)
            {
                char* witchJailMsg = "\nYOU ROLLED A 1! Oh how you anger me...\n I'm teleporting you to prison for getting such an awful number >:(\n";
                print1d(witchJailMsg, strlen(witchJailMsg), 120, 120);
                currentPlayer.isJailed = true;
                currentPlayer.jailedCounter += 1;
                currentPlayer.pos = 4;
            }
            else if(isPrime(num))
            {
                printf("\n🤯You rolled a LUCKY %d\n",num);
                sleep_ms(500);
                printf("Primes fill me with such glee! You must be rewarded.\n");
                sleep_ms(500);
                int luckyNum = getRandNum(
                    config.bonusrange.min,
                    config.bonusrange.max
                    );
                showPersonalBalanceUpdate(pendingPlayerBalance, pendingPlayerBalance + luckyNum);
                pendingPlayerBalance += luckyNum;
            }
            else
            {
                printf("\nLady luck frowns upon you and hands you a pitiful %d\n",num);
                sleep_ms(500);
                printf("I loathe composite numbers... I'll be taking from your savings account.\n");
                sleep_ms(500);
                int unluckyNum = getRandNum(
                    config.penaltyrange.min,
                    config.penaltyrange.max
                    );

                if(pendingPlayerBalance < unluckyNum)
                {
                    char* bankruptcyStatement = "Oh What's this? Your balance... It's so incredibly empty.\n";
                    char* bankruptcyStatement2 = "I'm afraid you're going to have to talk to Wumpus...\n";
                    print1d(bankruptcyStatement, strlen(bankruptcyStatement), 200, 200);
                    print1d(bankruptcyStatement2, strlen(bankruptcyStatement2), 120, 120);
                    continuePrompt();
                    currentPlayer.isBankrupt = true;
                    STATEKEY = sellPropertyEvent(&currentPlayer.isBankrupt, 
                                                config, STATEKEY, STATEKEY_OFFSET,
                                                currentPlayerKey, unluckyNum, 
                                                &pendingPlayerBalance);
                }
                if(currentPlayer.isBankrupt)
                {
                    setRed
                        printf("\nThere's nothing you can do to!\n");
                    resetColor

                    sleep_ms(500);
                    updatedGame = saveGame(currentPlayer, currentPlayerKey, 
                                            opposingPlayer, enemyPlayerKey,
                                            lstate);
                    continuePrompt();
                    return updatedGame;
                }
                showPersonalBalanceUpdate(pendingPlayerBalance, pendingPlayerBalance - unluckyNum);
                pendingPlayerBalance -= unluckyNum;
            }

            continuePrompt();
            break;
        }
        case 2:         // player lands on the electric company
        case 7:         // player lands on the railroad
        {
            isHouse = false;
            // 2 and 7 are non house types and cannot be renovated
        }
        case 1:         // player lands on the tree house
        case 3:         // player lands on the beach house
        case 5:         // player lands on the castle 
        case 8:         // player lands on the igloo 
        case 9:         // player lands on the farm house
        {

            // get the property index for the current position
            int propIndex = readStatekeyAtIndex(STATEKEY,pos,STATEKEY_OFFSET);
            
            bool isOwnedByOpponent = playerOwns(enemyPlayerKey, propIndex);     // flag for enemy property ownership
            bool isOwnedByPlayer = playerOwns(currentPlayerKey, propIndex);     // flag for current player property ownership
            bool isRenovated = (propIndex == 3 || propIndex == 4) && isHouse;   // check if property has been renovated
            
            // get the current property's cost
            int propertyCost = getPropertyCost(pos,config.electricCost,config.railCost);

            // if the property is owned by the bank and the player has enough capital, give the player the choice to purchase the property
            if((propIndex == 0) && pendingPlayerBalance >= propertyCost)
            {
                showPendingBalance(pendingPlayerBalance);

                setYellow
                    printf("\nPROPERTY COST: [%d 💰]\n",propertyCost);
                resetColor
                sleep_ms(500);

                if(playerDialogue("\n[B]uy property\n[E]nd turn","BE"))
                { // if the player buys the property
                    pendingPlayerBalance -= propertyCost; // subtract from balance
                    STATEKEY = mutateStatekeyAtIndex(
                        STATEKEY, pos,
                        currentPlayerKey, STATEKEY_OFFSET
                        ); // update statekey to reflect property purchase

                    setGreen
                        printf("\nYou have successfully bought the %s\n",getPropertyName(pos));
                    resetColor

                    showPersonalBalanceUpdate((pendingPlayerBalance + propertyCost), pendingPlayerBalance);
                    continuePrompt();
                }
            }
            // property is owned by the bank but the player doesn't have enough money
            else if((propIndex == 0) && pendingPlayerBalance < propertyCost)
            {
                
                newL
                setRed
                    printf("\nYou do not have enough money to purchase this property❗");
                resetColor

                sleep_ms(500);
                continuePrompt();
            }
            else if(isOwnedByPlayer)
            {
                if(!isHouse)            // player owns a non house property
                {

                    newL
                    setGreen
                        printf("\nYou own this industrial complex 👓");
                    resetColor

                    sleep_ms(500);
                    continuePrompt();
                }
                else if(isRenovated)    // player has already renovated the property
                {
                    newL
                    setGreen
                        printf("\nYou own this property and have already renovated it 👍");
                    resetColor

                    sleep_ms(500);
                    continuePrompt();
                }
                else                    // player owns a house property that has not been renovated
                {
                    int renovationCost = config.renovationCost; // get the renovation cost from settings

                    if(pendingPlayerBalance >= renovationCost) // check if the player has enough capital to renovate the property
                    {
                        showPendingBalance(pendingPlayerBalance);

                        setYellow
                            printf("\nRENOVATION COST: [%d 💸]\n",renovationCost); 
                        resetColor

                        sleep_ms(500);

                        if(playerDialogue("\n[R]enovate Property\n[E]nd Turn:","RE")) // ask if the player would like to renovate the property
                        {
                            STATEKEY = mutateStatekeyAtIndex(    // update the state key
                                STATEKEY, pos,
                                currentPlayerKey+2, STATEKEY_OFFSET     // + 2 means the property is renovated
                            ); 

                            setGreen
                                printf("\nYou have successfully renovated the %s\n",getPropertyName(pos));
                            resetColor

                            showPersonalBalanceUpdate(pendingPlayerBalance, pendingPlayerBalance - renovationCost);
                            pendingPlayerBalance -= renovationCost;     // player pays renovation cost
                            continuePrompt();
                        }
                    }
                    else // The player does not have enough capital to renovate the property
                    {
                        newL
                        setRed
                            printf("\nYou do not have enough capital to renovate this property ❗");
                        resetColor

                        sleep_ms(500);
                        continuePrompt();
                    }
                }
            }

            if(isOwnedByOpponent) // if the property belongs to the opposing player
            {

                setRed
                    printf("\n\nYou heve landed on a property that is owned by %s.\nThe owner loudly demands their alms 👺!\n",opposingPlayer.name);
                resetColor

                printf("\n[Press ENTER to pay rent]\n");
                getchar();

                int rent = getRent(pos,roll,                // calculate rent
                                    config.electricMulti,
                                    config.railRent);

                rent = isRenovated ? rent * 2 + 1 : rent;   // if the property is renovated rent is *2 + 1

                sleep_ms(200);

                setGreen
                    printf("RENT: [%d 🤑]\n",rent);
                resetColor

                sleep_ms(500);

                if(pendingPlayerBalance < rent)             // check if the player has enough capital to pay rent
                { 

                    currentPlayer.isBankrupt = true;        // for all intents and purposes, you are BANKRUPT!!... until further notice    
                    print1d("\n...",strlen("\n..."),300,300);

                    char* bankruptcyStatement = "Uh oh.. It seems as though you don't have enough money to pay rent\n";
                    char* bankruptcyStatement2 = "You're going to the Wumpus Compound...\n";
                    setRed
                        print1d(bankruptcyStatement, strlen(bankruptcyStatement),100,100);
                        print1d(bankruptcyStatement2, strlen(bankruptcyStatement2),100,100);
                    resetColor

                    sleep_ms(500);
                    STATEKEY = sellPropertyEvent(&currentPlayer.isBankrupt, config, STATEKEY,
                                                STATEKEY_OFFSET, currentPlayerKey, rent, 
                                                &pendingPlayerBalance);

                    if(currentPlayer.isBankrupt)
                    {
                        setRed
                            printf("\nThere's nothing you can do to!\n");
                        resetColor

                        sleep_ms(500);
                        updatedGame = saveGame(currentPlayer, currentPlayerKey, 
                                                opposingPlayer, enemyPlayerKey,
                                                lstate);
                        continuePrompt();
                        return updatedGame;
                    }
                }
                currentPlayer.rentCounter += 1; // increase rent counter
                showPersonalBalanceUpdate(pendingPlayerBalance, pendingPlayerBalance - rent);
                pendingPlayerBalance -= rent;
                pendingOpponentBalance += rent;

                continuePrompt();

            }
        }
    }
    clear
    showGameStatus(updatedGame);
    showBalanceUpdate(
        currentPlayer.balance, pendingPlayerBalance, currentPlayer.name,
        opposingPlayer.balance, pendingOpponentBalance, opposingPlayer.name);

    lstate.STATEKEY = STATEKEY;                             // save gamestate

    currentPlayer.balance = pendingPlayerBalance;           // save current player balance

    opposingPlayer.balance = pendingOpponentBalance;        // save enemy player balance

    updatedGame = saveGame(currentPlayer, currentPlayerKey, // save game
                            opposingPlayer, enemyPlayerKey,
                            lstate);

    continuePrompt();

    return updatedGame;
}

/*
    A dynamic game UI component that displays the current status of the game
    @param game the game package containing all game data
*/
void showGameStatus(struct gamepkg game)
{
    clear
    char* p1Properties = getAllPlayerProperties(game.state.STATEKEY,
                                                STATEKEY_OFFSET, 1);
    char* p2Properties = getAllPlayerProperties(game.state.STATEKEY,
                                                STATEKEY_OFFSET, 2);



    int currentPlayerIndex = game.state.activePlayer - 1;
    Player p1 = game.arrPlayerContainer[0];
    Player p2 = game.arrPlayerContainer[1];
    
    printf("\nPlayer 1: %s's Statistics\n",p1.name);
    printf("properties:");
    if(strlen(p1Properties) < 1)
    {
        setRed
        p1Properties = " NONE";
    }
    else
        setYellow

    printf("%s\n",p1Properties);
    resetColor    

    switch(p1.pos)
    {
        case 6:
            setPurple
            break;
        case 4:
            setRed
            break;
        case 2:
        case 7:
            setYellow
            break;
        default:        
            setCyan
            break;
    }

    printf("position: %d ",p1.pos);

    setGreen
        printf("balance: 💲%d\n",p1.balance);
    resetColor

    printf("\nPlayer 2: %s's Statistics\n",p2.name);
    printf("properties:");

    if(strlen(p2Properties) < 1)
    {
        setRed
        p2Properties = " NONE";
    }
    else
        setYellow

    printf("%s\n",p2Properties);
    resetColor    

    switch(p2.pos)
    {
        case 6:
            setPurple
            break;
        case 4:
            setRed
            break;
        case 2:
        case 7:
            setYellow
            break;
        default:        
            setCyan
            break;
    }

    printf("position: %d ",p2.pos);

    setGreen
        printf("balance: 💲%d\n",p2.balance);
    resetColor

    if(p1.isJailed)
    {
        setRed
            printf("\nIMPRISONED: [%s]\n",p1.name);
        resetColor
    }
    if(p2.isJailed)
    {
        setRed
            printf("\nIMPRISONED: [%s]\n",p2.name);
        resetColor
    }

    char* DIVIDER = createDivider(' ',1);

    setGreen
        printf("\n%s%s's TURN%s\n",
        DIVIDER,
        game.arrPlayerContainer[currentPlayerIndex].name,
        DIVIDER 
        );
    resetColor
}

/*
    Populates the wincontext list given the context type
    @param arrContext[] a list of contexts that tell the game how a winner was decided
    @param context the wincontext type to use
    @returns arrContext that is populated with the given wincontext
*/
enum winContext* populateContext(enum winContext arrContext[], enum winContext context)
{
    if(arrContext[0] != NOCONTEXT && arrContext[1] == NOCONTEXT)
        arrContext[1] = context;
    else
        arrContext[0] = context;

    return arrContext;
}

/*
    Updates the winstate variable contained in state and decides who to crown as the winner
    @param winsettings a struct of type winconditions that contains winner determinants
    @param p1 player1's data
    @param p2 player2's data
    @returns an updated winstate that has been through all winsettings checks
*/
struct winstate updateWinState(winconditions winsettings, Player p1, Player p2)
{
    struct winstate localWinstate = winsettings.winstate;

    if(p1.isBankrupt)
    {
        localWinstate.winRationale = populateContext(localWinstate.winRationale, ENEMY_BANKRUPTCY); // populate context list with bankruptcy
        localWinstate.winner = PLAYER2;
        return localWinstate;
    }
    if(p2.isBankrupt)
    {
        localWinstate.winRationale = populateContext(localWinstate.winRationale, ENEMY_BANKRUPTCY); // populate context list with bankruptcy
        localWinstate.winner = PLAYER2;
        return localWinstate;
    }

    unsigned int requiredFlags = winsettings.isSimul ? 2 : 1;                                     // check if 2 flags are required
    unsigned int p1Flags = 0;
    unsigned int p2Flags = 0;

    bool checkLosingBalance = winsettings.arrWintoggles[0] == DISABLED ? false : true;            // if losing balance has been enabled from settings
    bool checkWinningBalance = winsettings.arrWintoggles[1] == DISABLED ? false : true;           // if winning balance has been enabled from settings

    int floor = winsettings.losingBalance;
    int ceil = winsettings.winningBalance;
    
    if(checkLosingBalance)
    {
        if(p1.balance <= floor)
        {
            p2Flags += 1;
            populateContext(localWinstate.winRationale, ENEMY_LOSING_BALANCE);
        }
        if(p2.balance <= floor)
        {
            p1Flags += 1;
            populateContext(localWinstate.winRationale, ENEMY_LOSING_BALANCE);
        }
    }
    if(checkWinningBalance)
    {
        if(p1.balance >= ceil)
        {
            p1Flags += 1;
            populateContext(localWinstate.winRationale, REACHED_WINNING_BALANCE);
        }
        if(p2.balance >= ceil)
        {
            p2Flags += 1;
            populateContext(localWinstate.winRationale, REACHED_WINNING_BALANCE);
        }
    }

    if((p1Flags >= requiredFlags) || (p2Flags >= requiredFlags))
    {
        if(p2Flags >= requiredFlags && p1Flags >= requiredFlags)
            localWinstate.winner = TIE;
        else if(p2Flags >= requiredFlags)
            localWinstate.winner = PLAYER2;
        else
            localWinstate.winner = PLAYER1;
    }
    return localWinstate;
}
