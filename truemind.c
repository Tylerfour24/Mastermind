#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void game(char *attempt, char *answer, int *redcount, int *whitecount);

int main(void)
{
	srand(time(NULL));

	int place1 = ((rand() % 9) + 1);
	int place2 = ((rand() % 9) + 1);
	int place3 = ((rand() % 9) + 1);
	int place4 = ((rand() % 9) + 1);

	char attempt[5];
	char answer[5];
	int index;
	int *redcount = malloc(sizeof(int));
	*redcount = 0;
	int *whitecount = malloc(sizeof(int));
	*whitecount = 0;
	int guesscount = 0;

	answer[0] = place1;
	answer[1] = place2;
	answer[2] = place3;
	answer[3] = place4;

	printf("Let's play some mastermind...\nI'm thinking of a four digit number.\nThere are no zeroes!\n");

	while(*redcount != 4) {
		*redcount = 0;
		*whitecount = 0;
		
		printf("Please enter your 4-digit guess: ");
		fgets(attempt, sizeof(attempt)+1, stdin);
		
		if(attempt[4] != '\n') {
			while(!strchr(attempt, '\n')) {
				fgets(attempt, sizeof(attempt)+1, stdin);
			}
			attempt[4] = '\0';
		}

		else {
			attempt[4] = '\0';
		}

		for(index = 0; index < 4; index++) {
			attempt[index]-='0';
		}
	
		game(attempt, answer, redcount, whitecount);
		printf("%dRed, %dWhite\n", *redcount, *whitecount);
		guesscount += 1;
	}
	printf("You won in %d guesses!\n", guesscount);
	free(redcount);
	free(whitecount);
}
	

void game(char *attempt, char *answer, int *redcount, int *whitecount) {
	int index = 0;
	int altindex = 0;
	char paranswer[5];
	char parattempt[5];
	
	strncpy(&paranswer[index], &answer[index], sizeof(answer)+1);
	strncpy(&parattempt[index], &attempt[index], sizeof(attempt)+1);

	for(index = 0; index < 4; index++) {
		if(parattempt[index] == paranswer[index]) {
			*redcount += 1;
			paranswer[index] = ' ';
			parattempt[index] = '\t';
		}
	}
	for(index = 0; index < 4; index++) {
		for(altindex = 0; altindex < 4; altindex++) {
			if(altindex == index) {
				;
			}
			else if(parattempt[altindex] == paranswer[index]) {
				*whitecount += 1;
				paranswer[index] = ' ';
				parattempt[altindex] = '\t';
			}
		}
	}
}
