/*
    This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
    learned. I have constructed the functions and their respective algorithms and corresponding code all by myself. The
    program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole
    or otherwise plagiarized the work of other students and/or persons.
    Aaron NIcholas Lizardo Gumapac 
    ID: 12113495 

*/


/*
    Description: Property...Property is a terminal-based take on Monopoly written entirely in C.
    Programmed by: Aaron Nicholas Lizardo Gumapac
    Last modified: Feb 6, 2022
    Version: v8
    Acknowledgements: 
        Program Architecture: SICP. Structure and interpretation of computer programs. Retrieved February 4, 2022, from
        https://mitpress.mit.edu/sites/default/files/sicp/full-text/book/book.html 
        C language Specifics: Computerphile. YouTube. Retrieved February 4, 2022, from
        https://www.youtube.com/user/Computerphile/
        Shared Libraries: https://docencia.ac.upc.edu/FIB/USO/Bibliografia/unix-c-libraries.html
        Problem Solving Techniques: Ms. Shirley Chu, DLSU CCPROG1 Instructor
*/
//    Repo link: https://github.com/aarnich/Property...Property

#include "runtime_headers/GameLoop.h"
#include "runtime_headers/Settings.h"

/*
    Style guide:
    -- Colored print statements are indented between a setter and a resetter
*/

/*
    This function begins the game and calls game functions
    @param game the game package that contains all game information
    @returns a game package after the game is finished
*/
struct gamepkg playGame(struct gamepkg game)
{
    struct gamepkg lgame = game;                    // localize parameter in order to minimize errors

    printf("\nRandomizing first player =>> ");
    lgame.state.activePlayer = getRandNum(1, 2);    // randomize the first player

    sleep_ms(500);

    // get the opening player's name
    int firstkey = lgame.state.activePlayer - 1;    // decrease by one, arrays start counting at 0
    char *strFirstPlayer = lgame.arrPlayerContainer[firstkey].name; 

    sleep_ms(500);
    printf("%s will go first", strFirstPlayer);     // print opening player's name
    sleep_ms(500);
    clearbuff                                       // flush buffer to avoid unwanted behaviour
    continuePrompt();                               // getchar clears buffer beforehand

    // check if the game should continue
    while (continueGame(lgame.state.SETTINGS.winsettings.winstate.winner))
    {
        // pass localized game onto updategame and receive an updated package that has ran all player events
        lgame = updateGame(lgame);

        // update player values and change active player to the next
        updatePlayer(&lgame.state.activePlayer,
                     &lgame.arrPlayerContainer[0].isJailed, 
                     &lgame.arrPlayerContainer[1].isJailed);
    }

    return lgame;
}

/*
    Creates a struct gamepkg with initial game values and asks the users to configure
    settings and enter their names 
    @returns a game with intitial values
*/
struct gamepkg initializeGame()
{

    struct gamestate initstate = initializeGamestate();     // initialize a gamestate variable with basic values
    struct Player *arrPlayers = malloc(512);                // initialize a player array with size 512
    arrPlayers[0] = initializePlayer(initstate.SETTINGS);   // create player 1 with initial values and store in arrPlayers[0]
    arrPlayers[1] = initializePlayer(initstate.SETTINGS);   // create player 2 with initial values and store in arrPlayers[1]

    // create game variable that contains players and settings
    struct gamepkg game;
    game.state = initstate;               // store initial state into game.state
    game.arrPlayerContainer = arrPlayers; // store player array into arrPlayerContainer

    // return a game variable with initial values that has been through player customization
    return game;
}

/*
    Displays a game manual
*/
void displayManual()
{
    printf("\n\nAt the start of the game, players do not own any property. All properties on the board are owned by the Bank.\nAll properties owned by the Bank are up for sale and are not renovated.\nThe Bank has unlimited cash. The smallest denomination in this game is 1.");
    printf("\n\nPlayers take turn in rolling the dice to move clockwise around the board.\nAt each turn, the player rolls a dice to determine the number of spaces he moves on the board.\nThe player may land on:\n->Go (position 0),\n->on Jail Time (position 4), \n->on Feelin’ Lucky (position 6), or \n->on a property\n->(house properties at positions 1, 3, 5, 8, 9, electric company at position 2, and railroad at position 7). \nBased on the space where the player lands on, different actions may take place.\n\n");
}

/*
    Displays a short skit that acts as the first introduction to the game
*/
int main()
{
    srand((unsigned)time(NULL));

    clear 

    introScene(getRandNum(1, 2));           // 50% chance of getting the easter egg 😎

    continuePrompt();               
 
    char choice;
    struct gamepkg game = initializeGame(); // initialize firt gamepkg struct

    do
    {
        printf("\n[G] Start\n");
        printf("[S] Settings\n");
        printf("[I] Manual\n");
        printf("[E] Exit\n");

        char startingInputs[4] = "GSIE";
        choice = handleInput(startingInputs, strlen(startingInputs));
        switch (choice)
        {
            case 'E': // the player exits the game
                break;
            case 'S':
                game.state.SETTINGS = settingsPrompt(game.state.SETTINGS);
                break;
            case 'G':
                do
                {
                    game.arrPlayerContainer[1] = initializePlayer(game.state.SETTINGS);// update player settings
                    game.arrPlayerContainer[0] = initializePlayer(game.state.SETTINGS);// update player settings
                    char **ptrP1Name = &game.arrPlayerContainer[0].name; // change player 1 name
                    fetchPlayerName(ptrP1Name);
                    ptrP1Name = NULL;

                    char **ptrP2Name = &game.arrPlayerContainer[1].name; // change player 2 name
                    fetchPlayerName(ptrP2Name); 
                    ptrP2Name = NULL;

                    game = playGame(game);                              // begin the primary game loop

                    clear

                    // display ending screen after the game ends
                    displayEndingScreen(game.state.SETTINGS.winsettings.winstate,
                                        game.arrPlayerContainer[0],
                                        game.arrPlayerContainer[1]);
                    continuePrompt();

                    // prompt for a replay
                    printf("Press [G] to play again\n");
                    printf("Press [E] to exit\n");
                    char exitInputs[2] = "GE";
                    choice = handleInput(exitInputs, strlen(exitInputs));
                    if(choice == 'G') // reset relevant settings
                    {
                        game.state.SETTINGS.winsettings.winstate = initializeWinstate();
                        game.state.STATEKEY = STARTING_STATEKEY;
                    }
                } 
                while (choice == 'G');

                break;
            case 'I':
                displayManual();
                continuePrompt();
                newL
                break;

        }
    } 
    while (choice != 'E');

    char exitMsg[] = "\nCome back with better players.\n";
    print1d(exitMsg, strlen(exitMsg), 200, 200);

    return 0;
}