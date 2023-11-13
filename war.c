/*
*Author: Kyle Kline, kkline2019@my.fit.edu
*Course: CSE 1001, Section 05 Fall 2019
*Filename: war.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shuffle(int *, int);
int check_hand(int, int *);
void deal_hand(int *, int *, int *);
void card(int);

int main(void){
	printf("Welcome to war!\n");
	/*Set up an array for a deck with 52 cards,
	*one index in the array represents one card,
	*and an array for both players hands.*/
	int deck[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51};
	int player_1[104];
	int player_2[104];
	
	char player_1_card[2], player_2_card[2];
	char ready;
	int card_length = sizeof(player_1_card) / sizeof(player_1_card[0]);
	int deck_length = sizeof(deck) / sizeof(deck[0]);
	
	/*This takes the array of integers and reorders them*/
	printf("Shuffling deck...\n");
	shuffle(deck, deck_length);
	
	/*This function deals both player 26 cards from the deck */
	printf("Dealing hands...\n\n");
	deal_hand(deck, player_1, player_2);
	
	//The 2 length variables are set to keep track of the number of cards in each players decks.
	
	int length1 = 26;
	int length2 = 26;
	
	int cardnum1, cardnum2;
	do{
		
		printf("Would you like to play(p) or exit(e): ");
		scanf(" %c", &ready);
		printf("\n");
		/*These two if statements check whether the user entered an e or a p.
		*If the user entered an e game stops and prints that the game is a tie.
		*If the user enters p the game continues.
		*Anything else and the user will be asked again to enter something.
		*/
		if(ready == 'e' || ready == 'E'){
			printf("The game is a tie.\n\n");
			break;
		}
		else if(ready != 'p' && ready != 'P'){
			printf("Please enter e or p.\n");
			continue;
		}
		
		printf("Player 1's card: ");
		card(player_1[0]);
		
		printf("Player 2's card: ");
		card(player_2[0]);
		
		/*By taking the remainder of the first element of each array divided by 13
		*I am able to compare the number of each card and see which card is greater.*/
		cardnum1 = player_1[0] % 13;
		cardnum2 = player_2[0] % 13;
		
		/*In the case that Player 1's card is greater than Player 2's
		*Both cards are added to the end of Player 1's hand
		*Then all the cards in both hands are moved up by one.*/
		if(cardnum1 > cardnum2){
			printf("Player 1 wins this round! Awarding cards to Player 1...\n\n");
			player_1[length1] = player_1[0];
			length1++;
			player_1[length1] = player_2[0];
			length2--;
			for(int i = 0; i < length1; i++){
				player_1[i] = player_1[i + 1];
			}
			for(int i = 0; i < length2; i++){
				player_2[i] = player_2[i + 1];
			}
		}
		/*In the case that Player 2's card is greater than Player 1's
		*Both cards are added to the end of Player 2's hand
		*Then all the cards in both hands are moved up by one.*/
		else if(cardnum2 > cardnum1){
			printf("Player 2 wins this round! Awarding cards to Player 2...\n\n");
			player_2[length2] = player_2[0];
			length2++;
			player_2[length2] = player_1[0];
			length1--;
			for(int i = 0; i < length1; i++){
				player_1[i] = player_1[i + 1];
			}
			for(int i = 0; i < length2; i++){
				player_2[i] = player_2[i + 1];
			}
		}
		/*If Player 1 and Player 2's cards are equal they enter battle
		*Here the both players comper the fifth card in their hands.
		*With the winner getting the cards in the losers hand from the first to the fifth.
		*Then all the cards in each players hands are moved up by five.
		*/
		else{
			while(cardnum1 == cardnum2){
				printf("These cards match time for a battle.\n");
				printf("Drawing 3 cards from each player...\n");
				
				printf("Player 1's card: ");
				card(player_1[4]);
				printf("Player 2's card: ");
				card(player_2[4]);
				cardnum1 = player_1[4] % 13 + 2;
				cardnum2 = player_2[4] % 13 + 2;
				printf("\n");
				if(cardnum1 > cardnum2){
					printf("Player 1 wins this round! Awarding Player 1 cards...\n\n");
					if(length2 < 5){
						length2 = 0;
						break;
					}
					for(int i = 0; i < 5; i++){
						player_1[length1] = player_1[i];
						length1++;
					}
					for(int i = 0; i < 5; i++){
						player_1[length1] = player_2[i];
						length1++;
						length2--;
					}
					length1 = length1 - 5;
				}
				else if(cardnum2 > cardnum1){
					printf("Player 2 wins this round! Awarding Player 2 cards...\n\n");
					if(length1 < 5){
						length1 = 0;
						break;
					}
					for(int i = 0; i < 5; i++){
						player_2[length2] = player_2[i];
						length2++;
					}
					for(int i = 0; i < 5; i++){
						player_2[length2] = player_1[i];
						length2++;
						length1--;
					}
					length2 = length2 - 5;										
				}
				for(int i = 0; i < length1; i++){
					player_1[i] = player_1[i + 5];
				}
				for(int i = 0; i < length2; i++){
					player_2[i] = player_2[i + 5];
				}
			}
		}
	//When the length of the first array or the second array reach 0 the game is over and you exit the while loop.
	}while(length1 > 0 && length2 > 0);
	if(length1 == 0){
		printf("Player 2 wins!\n");
	}
	else if(length2 == 0){
		printf("Player 1 wins!\n");
	}
	printf("Goodbye! Thank you for playing war!");
	return 0;
}

void shuffle(int *full_deck, int len){
	/*This function will take the full deck and the deck length
	*Then put the cards up to that number in a random order.*/
	srand((unsigned)time(NULL));
	if(len > 1){
		int i, k, t;
		for(i = 0; i < (len - 1); i++){
			k = i + rand() / (RAND_MAX / (len - i) + 1);
			t = full_deck[k];
			full_deck[k] = full_deck[i];
			full_deck[i] = t;
		}
	}
}

int check_hand(int hand_size, int *hand){
	
}

void deal_hand(int *in_deck, int *hand1, int *hand2){
	/*This function goes into a for loop and has two variables equal to 0,
	*all cards in the array whose place is even is given to player 1, and
	*all cards in the array whose place is odd is given to player 2*/
	int j = 0;
	int k = 0;
	for(int i = 0; i < 52; i++){
		if(i % 2 == 0){
			hand1[j] = in_deck[i];
			j++;
		}
		else{
			hand2[k] = in_deck[i];
			k++;
		}
	}
}
void card(int number){
	/*Next I need to establish what the card value is for the top card in the deck. 
	*The variables cardnum 1 and 2 will tell us what number the card is by taking the remainder of the top card divided by 13 then plus 2,
	*we need a plus 2 because we start at 0 and the first card is a two.
	*For the suit we divide the top card by 13 and depending on if the number is a 0, 1, 2, or 3 it is given a suit.
	*/
	int cardnum = number % 13 + 2;
	int cardsuit = number / 13;
	if(cardnum >= 2 && cardnum <= 10){
		printf("%d", cardnum);
	}
	else if(cardnum == 11){
		printf("J");
	}
	else if(cardnum == 12){
		printf("Q");
	}
	else if(cardnum == 13){
		printf("K");
	}
	else if(cardnum == 14){
		printf("A");
	}
	if(cardsuit == 0){
		printf("S\n");
	}
	else if(cardsuit == 1){
		printf("D\n");
	}
	else if(cardsuit == 2){
		printf("H\n");
	}
	else if(cardsuit == 3){
		printf("C\n");
	}
}
