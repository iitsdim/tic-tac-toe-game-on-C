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
#include <string.h>

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


int placeMarkByHumanPlayer(int gameBoard[3][3], int mark) {
	int id;//ask the human to place the mark
	scanf("%d", &id);
	for (int i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j)
			if(posId(i, j) == id && gameBoard[i][j] == EMPTY) {
				gameBoard[i][j] = mark; //id marked
				return 1;
			}
			
	return 0;
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

int dp[(1<<9)][(1<<9)];
int move[(1<<9)][(1<<9)];

int CalcDp(int maskA, int maskB) {
	int *res = &dp[maskA][maskB];
	if(*res != -1)
		return *res;
	
	int gameBoard[3][3] = {};
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			int id = posId(i,j)-1;
			if(maskA & (1<<id))
				gameBoard[i][j] = CROSS;
			if(maskB & (1<<id))
				gameBoard[i][j] = CIRCLE;
		}
	}
	
	if(hasWinner(gameBoard)) {
		return 0;
	}
	if(isFull(gameBoard)) {
		return 2;
	}
	
	move[maskA][maskB] = -1;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) if(gameBoard[i][j] == 0) {
			int id = posId(i,j)-1;
			int nxt = CalcDp(maskB, maskA | (1<<id));
			
			if(nxt == 0) {
				*res = 1;
				move[maskA][maskB] = id+1;
				return *res;
			}
			
			if(*res < nxt) {
				*res = nxt;
				move[maskA][maskB] = id+1;
			}
		}
	}
	
	if(*res == 1) *res = 0;
	
	return *res;
}

void fillDP() {
	for (int i = 0; i < (1<<9); ++i)
		for (int j = 0; j < (1<<9); ++j)
			dp[i][j] = -1;
}

int placeMarkByComputerPlayer(int gameBoard[3][3]) {
	int A = 0, B = 0;
	for (int i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j) {
			if(gameBoard[i][j] == CIRCLE) A |= (1<<(posId(i,j)-1));
			if(gameBoard[i][j] == CROSS) B |= (1<<(posId(i,j)-1));
		}
	
	CalcDp(B, A);
	int id = move[B][A];
	
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if(posId(i, j) == id) {
				gameBoard[i][j] = CROSS;
				return 1;
			}
		}
	}
	
	return 0;
}

int main() {
	fillDP();
	int games[10][3][3] = {};
	int currentPlayer = 1;
    int numOfHumanPlayers;
	int moves = 0;
	
	while(1) {
		printf("How many human players [1-2]?\n");
		scanf("%d", &numOfHumanPlayers);
		if(numOfHumanPlayers >= 1 && numOfHumanPlayers <= 2)
			break;
		puts("Incorrect number of human players, please try again");
	}
	
	while(1) {
		if(isFull(games[moves])) {
			break;
		}
		++moves;
		for (int i = 0; i < 3; i ++)
				for (int j = 0; j < 3; ++j)
					games[moves][i][j] = games[moves-1][i][j];
		if(currentPlayer <= numOfHumanPlayers) {
			printGameBoard(games[moves]);
		}
		if(currentPlayer == 1) {
			printf("Player 1, please place your mark [1-9]:\n");
			placeMarkByHumanPlayer(games[moves], CIRCLE); // 1 player move
		} else if(numOfHumanPlayers == 2) {
			printf("Player 2, please place your mark [1-9]:\n");
			placeMarkByHumanPlayer(games[moves], CROSS); // 2 player move
		} else {
			printf("Computer places the mark:\n"); //so 2 player is Computer
			placeMarkByComputerPlayer(games[moves]);
		}
		if(currentPlayer <= numOfHumanPlayers) {
			printGameBoard(games[moves]);
			puts("If you want to undo move/moves, please enter 'U' (without the quotes), otherwise enter 'C' (without the quotes)");
			int cnt = 0;
			char Undo[101];
			do {
				if(++cnt > 1) {
					printf("You last command was incorrect, please enter 'U' (without the quotes) if you want to undo move/moves, otherwise enter 'C' (without the quotes)\n");
				}
				scanf("%s", Undo);
			}while(strlen(Undo) > 1 || Undo[0] != 'C' && Undo[0] != 'U');
			
			if(Undo[0] == 'U') {
				cnt = 0;
				
				if(numOfHumanPlayers == 2) {
					printf("Please enter, how many moves you want to undo? [1, %d]\n", moves);
					int skip;
					do {
						if(++cnt > 1) {
							printf("You last command was incorrect, please enter number of moves you want to undo within interval [1, %d]\n", moves);
						}
						scanf("%d", &skip);		
					} while(skip < 1 || skip > moves);
					
					if(!(skip & 1)) {
						currentPlayer = 3 - currentPlayer;
					}
					moves -= skip;
				} else {
					printf("Please enter, how many moves you want to undo? [1, %d]\n", (moves + 1) / 2); //since almost half of moves was done by computer
					int skip;
					do {
						if(++cnt > 1) {
							printf("You last command was incorrect, please enter number of moves you want to undo within interval [1, %d]\n", (moves+1)/2);
						}
						scanf("%d", &skip);		
					} while(skip < 1 || skip > (moves+1)/2);
					
					moves -= 2*skip-1;
				}
				continue;
			}
		}
		
		if(hasWinner(games[moves])) {
			printGameBoard(games[moves]);
		
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
	
	printGameBoard(games[moves]);
	//gameBoard is full so DRAW
	printf("Draw game!\n");
	
    return 0;
}