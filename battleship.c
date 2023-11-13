#include <stdio.h>
#include <stdlib.h>

/*Function read_map it takes in parameters len and wid as how big the map is.
*maps1 is the map that you play the game against, and we check to make sure there are no errors.
*variable shots is how many shots the user wants to use which we check to see if the nber of shots are greater than
*or equal to *count which keeps track of how many boats are on the map.*/
void read_map(int len, int wid, char maps1[len][wid], int shots, int *count);
/*Function print_map takes variables len and wid to show how big the map is, and maps2
*is the map the user shows what spots the user tried already.*/
void print_map(int len, int wid, char maps2[len][wid]);
/*Function play_game takes maps3 as the map the user sees and makes guesses with,
*maps4 is the map the program checks to see if the user hit a boat or not,
*shots is how many shots the user can still use, count represents how many boats there are*/
void play_game(int len, int wid, char maps3[len][wid], char maps4[len][wid], int shots, int count);

int main(int argc, char *argv[]){
/*fin opens the file of the map the user wants to use to play the game.*/
	FILE *fin = fopen(argv[2], "r");
/*num array keeps track of the parameters listed at the top of each map.*/
	int num[2];
	
	for(int i = 0; i < 2; i++){	
		fscanf(fin, "%d", &num[i]);
	}
	
	int boats = 0;
/*shot takes the first parameter the user entered in the command line and turns it into a number*/
	int shot = atoi(argv[1]);
	int length = num[0];
	int width = num[1];
	char map[num[0]][num[1]];
	char map2[num[0]][num[1]];
	
/*This for loop copies the map the user wants to use for the program*/
	for(int i = 0; i < num[0]; i++){
		for(int j = 0; j < num[1]; j++){
			fscanf(fin, " %c", &map2[i][j]);
		}
	}

/*This for loop takes the map the user will seee and set all elements equal to '~'*/
	for(int i = 0; i < num[0]; i++){
		for(int j = 0; j < num[1]; j++){
			map[i][j] = '~';
		}
	}
	
	read_map(length, width, map2, shot, &boats);
	play_game(length, width, map, map2, shot, boats);
	fclose(fin);
}

void read_map(int len, int wid, char maps1[len][wid], int shots, int *count){
/*This for loop checks where ever the map has a 'B' and add a one to the count variable.*/
	for(int i = 0; i < len; i++){
		for(int j = 0; j < wid; j++){
			if(maps1[i][j] == 'B'){
				*count = *count + 1;
			}
		}
	}
/*This for loop checks to see that all elements in the map are either a 'B' or a '~'
*If an element appears that isn't a 'B' or '~' it'll print an error and end the program*/
	for(int i = 0; i < len; i++){
		for(int j = 0; j < wid; j++){
			if(maps1[i][j] != 'B' && maps1[i][j] != '~'){
				printf("This map has an error!");
				exit(-1);
			}
		}
	}
/*If the number of shots the user wants to use is less than the number of boats the map has
*The program will end as well*/
	if(shots < *count){
		printf("Captain you have to use more shots");
		exit(-1);
	}
}
void print_map(int len, int wid, char maps2[len][wid]){
/*This for loop shall print the map the user will see.*/
	for(int i = 0; i < len; i++){
		for(int j = 0; j < wid; j++){
			printf("%c", maps2[i][j]);
		}
		printf("\n");
	}
}

void play_game(int len, int wid, char maps3[len][wid], char maps4[len][wid], int shots, int count){
/*The variables coord1 and coord2 are the parameters that the user enters that act as coordinates for the map
*variable hit keeps track of all the times I hit a boat.*/ 
	int coord1, coord2;
	int hit = 0;
	while(shots > 0){
		printf("Map\n");
		print_map(len, wid, maps3);
		if(shots == 1){
			printf("%d shot remaining.\nCaptain please enter coordinates: ", shots);
		}
		else{
			printf("%d shots remaining.\nCaptain please enter coordinates: ", shots);
		}
		scanf("%d %d", &coord1, &coord2);
/*If the coordinates are larger than the maps parameters or less than zero
*It will not be a valid entry*/
		if((coord1 > len - 1 || coord1 < 0) || (coord2 > wid - 1 || coord2 < 0)){
			printf("Out of range\n");
		}
/*If the user enters a spot that has a 'B' on the other map and the map that we see still has a '~'
*The program will print "HIT" splace the element on the map we see with an 'H' 
*variable shots decreases by 1 and variable hit increases by 1*/
		else if(maps4[coord1][coord2] == 'B' && maps3[coord1][coord2] == '~'){
			printf("HIT!\n");
			maps3[coord1][coord2] = 'H';
			shots--;
			hit++;
		}
/*If the user enters a coordinate who's element is not a '~' a message will print
*stating that the user already tried this area.*/
		else if(maps3[coord1][coord2] != '~'){
			printf("Captain we already shot this area...\n");
		}
/*Anything else happens the program will print "MISS!" replace the element at those coordinates
*on the map we see with an 'M' and decrease variable shots by 1.*/
		else{
			printf("MISS!\n");
			maps3[coord1][coord2] = 'M';
			shots--;
		}
/*If the number of hits equals the variable count 
*a message will print saying that you won the game and then exit the while loop*/
		if(hit == count){
			print_map(len, wid, maps3);
			printf("Captain, we have sunk all the battleships. You win!");
			break;
		}
/*If the number of shots goes down to zero and the user hasn't hit all the boats yet
*a message will print saying you lose*/
		if(shots == 0){
			print_map(len, wid, maps3);
			printf("Captain, we ran out of shots. You lose!");
		}
	}
}


	
	
	
	
