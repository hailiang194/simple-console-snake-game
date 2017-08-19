#ifndef LOGIC_IN_GAME_H_
	#define LOGIC_IN_GAME_H_

#include "info-game.h"

#define TRUE 1
#define FALSE 0

int is_snake_point(const object_t *snake, int x, int y);
int is_eat_fruit(const object_t *snake, location_t fruit);
int is_game_over(const object_t *snake);


int is_snake_point(const object_t *snake, int x, int y)
{
	int i = 0;

	while(i < MAX_LENGTH_SNAKE && snake[i].isExist)
	{
		if(snake[i].location.x == x && snake[i].location.y == y)
			return TRUE;
		i++;
	}

	//(x, y) is not snake point
	return FALSE;
}

int is_eat_fruit(const object_t *snake, location_t fruit)
{
	return ((snake[0].location.x == fruit.x) && (snake[0].location.y == fruit.y));
}


int is_game_over(const object_t *snake)
{
	int headPointX = snake[0].location.x;
	int headPointY = snake[0].location.y;

	//snake is in block
	if((headPointX == WIDTH || headPointX == -1) || (headPointY == HEIGHT || headPointY == -1))
		return TRUE;

	//out of length
	if(snake[MAX_LENGTH_SNAKE - 1].isExist)
		return TRUE;

	int i = 1;

	//snake byte itself
	while(i < MAX_LENGTH_SNAKE && snake[i].isExist)
	{
		if(headPointX == snake[i].location.x && headPointY == snake[i].location.y)
			return TRUE;

		i++;
	}

	return FALSE;
}

#endif