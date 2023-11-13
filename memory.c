/*
*Author: Kyle Kline, kkline2019@my.fit.edu
*Course: CSE 1001, Section 05 Fall 2019
*Filename: memory.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_board(int length, int length2, char in_board[length][length2]);
void fill_board(int length, int length2, char in_board[length][length2]);
int main(void){
	/*The variable points keeps track of the number of points you get for matching letters.
	*size1 and size2 are set as to show how many rows and the length of columns.
	*/
	int points;
	int size1 = 4;
	int size2 = 4;
	char ready;
	/*row1 and column1 are used for the first guess while row1 and column1 are used for the second guess
	*/
	int row1, row2, column1, column2;
	/*board represents the board that is covered
	*board2 represents the board with the letters placed randomly
	*/
	char board[4][4] = {{'$', '$', '$', '$'}, {'$', '$', '$', '$'}, {'$', '$', '$', '$'}, {'$', '$', '$', '$'}};
	char board2[4][4];
	fill_board(size1, size2, board2);
	printf("Here's the board: \n\n");
	print_board(size1, size2, board);
	do{
		/*This prompts the user and asks them if the want to find a match or not
		*if the user enters 'Q' it exits the function, but if the user enters 'F' 
		*the game continues
		*/
		printf("Choose an option:\n(F) Find a match\n(Q) Quit\nChoice: ");
		scanf(" %c", &ready);
		if(ready == 'Q'){
			break;
		}
		else if(ready != 'F'){
			printf("Please enter either \'Q\' or \'F\'\n");
			continue;
		}
		printf("Pick first card (row, column): ");
		scanf("%d,%d", &row1, &column1);
		printf("Pick second card (row, column): ");
		scanf("%d,%d", &row2, &column2);
		/*After prompting the user for the first card and second card
		*if the variable on board2[row1][column1] == board2[row2][column2]
		*The user gets a point, board[row1][column1] = board2[row1][column1] and 
		*board[row2][column2] = board2[row2][column2] then prints the board.
		*It also checks to make sure the user hasn't entered the same position.
		*/
		if(board2[row1][column1] == board2[row2][column2] && (row1 != row2 || column1 != column2)){
			board[row1][column1] = board2[row1][column1];
			board[row2][column2] = board2[row2][column2];
			printf("Cards match you get a point!\n");
			points++;
			printf("Your current points: %d\n", points);
			printf("Here's the board: \n\n");
			print_board(size1, size2, board);
		}
		/*After prompting the user for the first and second card
		*if the variable at board2[row1][column1] != board2[row2][column2]
		*the user does not get a point, board[row1][column1] = board2[row1][column1] and
		*board[row2][column2] = board2[row2][column2] then prints the board to show what variables 
		*those spots equal then covers up those spots again.
		*/
		else{
			printf("Cards do not match try again. ");
			board[row1][column1] = board2[row1][column1];
			board[row2][column2] = board2[row2][column2];
			printf("Your current points: %d\n", points);
			printf("Here's the board: \n\n");
			print_board(size1, size2, board);
			board[row1][column1] = '$';
			board[row2][column2] = '$';
		}
	//When the points equals 8 becuase thats how many matches there are the game ends
	}while(points != 8);
	printf("Your total points: %d. Goodbye.", points);
}

void print_board(int length, int length2, char in_board[length][length2]){
	//This functions prints all the current variable in the array board in board format.
	printf("    %d   %d   %d   %d\n", 0, 1, 2, 3);
	for(int i = 0; i < length; i++){
		printf("%d ", i);
		for(int j = 0; j < length2; j++){
			printf("| %c ", in_board[i][j]);
		}
		printf("\n");
		printf("-----------------");
		printf("\n");
	}
}
void fill_board(int length, int length2, char in_board[length][length2]){
	//This function is meant to put random variables in board2 twice in a random order.
	/*For this I need a temporary array because I felt it was easier to set 
	*a 1-d array with random variables than a 2-d array.
	*/
	int num[16];
	int ran;
	srand(time(0));
	//Since I the board has 8 sets I only need 8 random numbers and copy duplicate them in the same array
	for(int i = 0; i < 8; i++){
		/*I used the random function returning a random variable from 65 to 90 since that's the ascii value
		*for A to Z
		*/
		num[i] = (rand() % (90 - 65 + 1)) + 65;	
		for(int j = 0; j < i; j++){
			while(num[i] == num[j] && i != j){
				num[i] = (rand() % (90 - 65 + 1)) + 65;
			}
		}
		
	}
	for(int i = 8; i < 16; i++){
		num[i] = num[i - 8];
	}
	int hold;
	//Since I didn't randomize the array with the duplicated numbers I need to randomize the array again.
	for(int i = 0; i < 16; i++){
		ran = rand() % 16;
		hold = num[i];
		num[i] = num[ran];
		num[ran] = hold;
	}
	/*All that's left is to put the variables in the temporary back into board2
	*Since the temporary array is type int when put into a character array
	*It's set as the letter that ascii value equals.
	*/
	int track = -1;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			track++;
			in_board[i][j] = num[track];
		}
	}
}