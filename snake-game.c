#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "info-game.h"
#include "logic-in-game.h"
#include "process-in-game.h"

void show_logo();
void game_option_scene();
void game_scene();

void game_over_scene(const object_t *snake);

int main()
{
	game_option_scene();
	return 0;
}

void show_logo()
{
	system("cls");
	FILE *logoFile = fopen("data/logo-text.txt", "r");

	while(!feof(logoFile))
	{
		char c = fgetc(logoFile);
		if(c == EOF)
			break;

		printf("%c", c);
	}

	fclose(logoFile);
}

void game_option_scene()
{
	show_logo();

	printf("\n\n");
	printf("1. START GAME\n");
	printf("2. CLOSE\n");

	int choose = 0;

	printf("> ");
	fflush(stdin);
	scanf("%d", &choose);

	switch(choose)
	{
		case 1:
			game_scene();
			break;
		case 2:
			exit(0);
			break;
		default:
			game_option_scene();
	}
}

void game_scene()
{
	object_t *snake = (object_t *)malloc(MAX_LENGTH_SNAKE * sizeof(object_t));
	location_t fruit;
	int direct;


	setup(snake, &fruit, &direct);
	show_game_scene(snake, fruit);
	printf("PRESS ANY KEY TO START!\n");
	getch();

	while(!is_game_over(snake))
		update(snake, &fruit, &direct);

	game_over_scene(snake);
}

void game_over_scene(const object_t *snake)
{
	system("cls");
	printf("\aGAME OVER\n");

	//get score
	int score = 1;

	while(score < MAX_LENGTH_SNAKE && snake[score].isExist)
	{
		score++;
	}

	printf("YOUR SCORE : %d\n", score);

	printf("PLAY AGIAN? (Y/N) ");

	char choose = ' ';

	fflush(stdin);
	scanf("%c", &choose);

	switch(choose)
	{
		case 'y':
		case 'Y':
			game_scene();
			break;
		case 'N':
		case 'n':
			game_option_scene();
			break;
		default:
			game_over_scene(snake);
	}
}