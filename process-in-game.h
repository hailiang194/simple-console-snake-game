#ifndef PROCESS_IN_GAME_H_
	#define PROCESS_IN_GAME_H_

#include <unistd.h>

#include "info-game.h"
#include "logic-in-game.h"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3


void setup(object_t *snake, location_t *fruit, int *direct);
void control(object_t *snake, int *direct);
void show_game_scene(const object_t *snake, location_t fruit);

int get_random(int n);
void set_fruit(location_t *fruit);
void set_location(location_t *object, int x, int y);

void update(object_t *snake, location_t *fruit, int *direct);
void update_snake(object_t *snake, location_t *fruit, int direct);

void setup(object_t *snake, location_t *fruit, int *direct)
{
	//set status of direction
	*direct = LEFT;

	//set new snake
	set_location( snake[0].location, WIDTH / 2, HEIGHT / 2);
	snake[0].isExist = TRUE;

	for(int i = 1; i < MAX_LENGTH_SNAKE;i++)
	{
		set_location( snake[i].location, 0, 0);
		snake[i].isExist = FALSE;
	}

	//set fruit location
	set_fruit(fruit);
}

void control(object_t *snake ,int *direct)
{
	int lastDirect = *direct;
	int hasTail = snake[1].isExist;

	if(kbhit())
	{
		char c = getch();
		switch(c)
		{
			case 'w':
			case 'W':
				if(lastDirect != DOWN || !hasTail)
					*direct = UP;
				break;
			case 'a':
			case 'A':
				if(lastDirect != RIGHT || !hasTail)
					*direct = LEFT;
				break;
			case 's':
			case 'S':
				if(lastDirect != UP || !hasTail)
					*direct = DOWN;
				break;
			case 'd':
			case 'D':
				if(lastDirect != LEFT || !hasTail)
					*direct = RIGHT;
			default:
				break;
		}

	}
}


int get_random(int n)
{
	return rand() % n;
}

void set_fruit(location_t *fruit)
{
	set_location(fruit, get_random(WIDTH), get_random(HEIGHT));
}

void set_location(location_t *object, int newX, int newY)
{
	object -> x = newX;
	object -> y = newY;
}


void update(object_t *snake, location_t *fruit, int *direct)
{
	control(snake,direct);
	update_snake(snake, fruit, *direct);
	show_game_scene(snake, *fruit);
	sleep(1);
}


void update_snake(object_t *snake, location_t *fruit, int direct)
{

	location_t *snakePointLocation = snake[0].location;
	int prevX = snake[0].location -> x;
	int prevY = snake[0].location -> y;
	
	//set location of snake's head point
	switch(direct)
	{
		case UP:
			set_location(snakePointLocation, prevX, prevY - 1);
			break;
		case DOWN:
			set_location(snakePointLocation, prevX, prevY + 1);
			break;
		case LEFT:
			set_location(snakePointLocation, prevX - 1, prevY);
			break;
		case RIGHT:
			set_location(snakePointLocation, prevX + 1, prevY);
			break;
		default:
			break;
	}

	int i = 1;

	int prev2X = 0, prev2Y = 0;

	//first, save old location -> prev
	//next, save location of next snake point -> done
	//finally, set next snake point to old location -> done

	
	while(i < MAX_LENGTH_SNAKE && snake[i].isExist)
	{
		
		prev2X = snake[i].location -> x; 
		prev2Y = snake[i].location -> y;		
		
		snake[i].location -> x = prevX;
		snake[i].location -> y = prevY;

		prevX = prev2X;
		prevY = prev2Y;
		i++;
	}

	if(is_eat_fruit(snake, *fruit))
	{
		snake[i].isExist = TRUE;
		snake[i].location -> x = prevX;
		snake[i].location -> y = prevY;
		set_fruit(fruit);
	}
}


void show_game_scene(const object_t *snake, location_t fruit)
{
	system("cls");
	printf("QUICK GUIDE :\n");
	printf("W - UP : A - LEFT : S - DOWN : D - RIGHT\n");
	const char SNAKE_HEAD_POINT = 'O';
	const char SNAKE_POINT = 'o';
	const char FRUIT_POINT = '*';
	const char BLOCK_POINT = '#';
	
	//print head row block
	for(int i = 0; i < WIDTH + 2; i++)
		printf("%c", BLOCK_POINT);
	printf("\n");

	//print snake, fruit, and inside 
	for(int i = 0; i < HEIGHT; i++)
	{
		printf("%c", BLOCK_POINT);
		for(int j = 0; j < WIDTH; j++)
		{
			if( is_snake_point(snake, j, i) )
			{
				if(j == snake[0].location -> x 
					&& i == snake[0].location -> y)
					printf("%c", SNAKE_HEAD_POINT);
				else
					printf("%c", SNAKE_POINT);
			}
			else if(fruit.x == j && fruit.y == i)
				printf("%c", FRUIT_POINT);
			else
				printf(" ");
		}

		printf("%c\n", BLOCK_POINT);
	}

	//print footer row block
	for(int i = 0; i < WIDTH + 2; i++)
		printf("%c", BLOCK_POINT);
	printf("\n");
}

#endif