#ifndef INFO_GAME_H_
	#define INFO_GAME_H_

#define WIDTH 20
#define HEIGHT 10

const int MAX_LENGTH_SNAKE = WIDTH * HEIGHT;

typedef struct LOCATION
{
	int x;
	int y;
} location_t;

typedef struct OBJECT
{
	location_t location;
	int isExist : 3;
} object_t;


#endif