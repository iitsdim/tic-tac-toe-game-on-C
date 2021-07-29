/**
 * ENGG1110 Problem Solving by Programming
 *
 * Course Project
 *
 * I declare that the project here submitted is original
 * except for source material explicitly acknowledged,
 * and that the same or closely related material has not been
 * previously submitted for another course.
 * I also acknowledge that I am aware of University policy and
 * regulations on honesty in academic work, and of the disciplinary
 * guidelines and procedures applicable to breaches of such
 * policy and regulations, as contained in the website.
 *
 * University Guideline on Academic Honesty:
 *   https://www.cuhk.edu.hk/policy/academichonesty/
 *
 * Student Name  : Tursynbay Dinmukhamed
 * Student ID    : 1155147558
 * Class/Section : 1110D
 * Date          : 11/2/2020
 */

#include <stdio.h>
/* NO other header files are allowed */ 

/* NO global variables are allowed */

/* Macros used to represent the state of each square */
#define EMPTY 0
#define CIRCLE 1
#define CROSS 2

void initGameBoard(int gameBoard[3][3]) {
    for (int i = 0; i < 3; ++i)
      for(int j = 0; j < 3; ++j)
        gameBoard[i][j] = EMPTY; //fill board empty
}

int posId(int i, int j) {
	return j+7-3*i; //returns what position is i, j in gameBoard
}

void printGameBoard(int gameBoard[3][3]) {
	for (int i = 0; i < 9; ++i) printf("=");
	printf("\n");
	for (int i = 0; i < 3; ++i) {
		for(int j = 0; j < 3; ++j) {
			printf("|");
			if(gameBoard[i][j] == CIRCLE) printf("O"); //Circle
			else if(gameBoard[i][j] == CROSS) printf("X"); //Cross
			else printf("%d", posId(i, j)); //Empty Position, I should print the number of i, j
			printf("|");
		}
		printf("\n");
	}
	for (int i = 0; i < 9; ++i) printf("=");
	printf("\n");
	//Just printing the gameBoard
}


void placeMarkByHumanPlayer(int gameBoard[3][3], int mark) {
	int id;//ask the human to place the mark
	scanf("%d", &id);
	for (int i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j)
			if(posId(i, j) == id) {
				gameBoard[i][j] = mark; //id marked
				return;
			}
			
	//
}


/* Note: the winner is the current player indicated in main() */
int hasWinner(int gameBoard[3][3]) {
    for (int i = 0; i < 3; ++i) {
		if(gameBoard[i][0] != EMPTY && gameBoard[i][0] == gameBoard[i][1] && gameBoard[i][1] == gameBoard[i][2]) //horizontal
			return 1;
		if(gameBoard[0][i] != EMPTY && gameBoard[0][i] == gameBoard[1][i] && gameBoard[1][i] == gameBoard[2][i]) //vertical
			return 1;
	}
	
	if(gameBoard[1][1] != EMPTY) {
		if(gameBoard[0][0] == gameBoard[2][2] && gameBoard[0][0] == gameBoard[1][1]) // diagonal
			return 1;
		if(gameBoard[0][2] == gameBoard[2][0] && gameBoard[2][0] == gameBoard[1][1]) // another diagonal
			return 1;
	}
	return 0;
}



/* Return 1 if the game board is full, otherwise return 0 */

int isFull(int gameBoard[3][3]) {
	for (int i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j)
			if(gameBoard[i][j] == EMPTY)
				return 0; //so this is empty place
	return 1; //there's no empty place
}


/* Determine the next move of the computer player.
   In Part 1, you are required to implement the following naive strategy:
   place the mark in the first empty space scanning from 1 to 9.
   You are welcome to design and implement better strategies in Part 2.
   IMPORTANT: Using other strategies in Part 1 will result in mark deduction.
              If you have better strategies, please use them in Part 2 instead. */

void placeMarkByComputerPlayer(int gameBoard[3][3]) {
	for (int id = 1; id <= 9; ++id) {
		//computer game
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) if(gameBoard[i][j] == EMPTY){
				if(posId(i, j) == id) {
					gameBoard[i][j] = CROSS; //computer marks CROSS
					return; //marked go back
				}
			}
		}
		
	}
	//can't move, board should be full
}


/* The main function */
int main() {
    /* Local variables */
    int gameBoard[3][3];    // Each element stores 0 (EMPTY), 1 (CIRCLE), or 2 (CROSS)
    int currentPlayer;      // 1: Player 1 (Human)   2: Player 2 (Human) or Computer Player
    int gameEnds;           // 0: The game continues   1: The game ends
    int numOfHumanPlayers;  // 1 or 2

    /* Initialize the local variables by invoking a function, using assignment statements, and reading the user input */
    initGameBoard(gameBoard);
    currentPlayer = 1;
    gameEnds = 0;
    printf("How many human players [1-2]?\n");
    scanf("%d", &numOfHumanPlayers);    // In Part 1, you can assume that the user input must be valid

    //printGameBoard(gameBoard);
    //printf("Player 1, please place your mark [1-9]:\n");
    //placeMarkByHumanPlayer(gameBoard, CIRCLE);
    //printf("Player 2, please place your mark [1-9]:\n");
    //placeMarkByHumanPlayer(gameBoard, CROSS);
	//printGameBoard(gameBoard);
    //Checked
	
	while(!isFull(gameBoard)) {
		printGameBoard(gameBoard);
		if(currentPlayer == 1) {
			printf("Player 1, please place your mark [1-9]:\n");
			placeMarkByHumanPlayer(gameBoard, CIRCLE); // 1 player move
		} else if(numOfHumanPlayers == 2) {
			printf("Player 2, please place your mark [1-9]:\n");
			placeMarkByHumanPlayer(gameBoard, CROSS); // 2 player move
		} else {
			printf("Computer places the mark:\n"); //so 2 player is Computer
			placeMarkByComputerPlayer(gameBoard);
		}
		
		if(hasWinner(gameBoard)) {
			printGameBoard(gameBoard);
		
			if(currentPlayer == 1) {
				printf("Player 1 wins! Congratulations!\n"); //1 player win
				return 0;
			}
			if(numOfHumanPlayers == 2) {
				printf("Player 2 wins! Congratulations!\n"); //2 player win
				return 0;
			}
			printf("Computer wins!\n"); //Computer win
			return 0;
		}
		
		currentPlayer = 3 - currentPlayer;
	}
	printGameBoard(gameBoard);
	//gameBoard is full so DRAW
	printf("Draw game!\n");

    return 0;
}