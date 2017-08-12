#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

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

int get_random(int n);
void set_fruit(location_t *fruit);
void set_location(location_t *object, int x, int y);

void setup(object_t *snake, location_t *fruit, int *direct);
void show_game_scene(const object_t *snake, location_t fruit);
void update(object_t *snake, location_t *fruit, int *direct);

int is_snake_point(const object_t *snake, int x, int y);
int is_eat_fruit(const object_t *snake, location_t fruit);
void control(int *direct);
void update_snake(object_t *snake, location_t *fruit, int direct);

int is_game_over(const object_t *snake);
void game_over_scene(const object_t *snake);

int main()
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
	return 0;
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

void setup(object_t *snake, location_t *fruit, int *direct)
{
	//set status of direction
	*direct = LEFT;

	//set new snake
	set_location( &(snake[0].location), WIDTH / 2, HEIGHT / 2);
	snake[0].isExist = TRUE;

	for(int i = 1; i < MAX_LENGTH_SNAKE;i++)
	{
		set_location( &(snake[i].location), 0, 0);
		snake[i].isExist = FALSE;
	}

	//set fruit location
	set_fruit(fruit);
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
				if(j == snake[0].location.x && i == snake[0].location.y)
					printf("%c", SNAKE_HEAD_POINT);
				else
					printf("%c", SNAKE_POINT);
			}
			else if(fruit.x == j && fruit.y == i)
				printf("%c", FRUIT_POINT);
			else
				printf(" ");
		}

		printf("#\n");
	}

	//print footer row block
	for(int i = 0; i < WIDTH + 2; i++)
		printf("%c", BLOCK_POINT);
	printf("\n");
}

void update(object_t *snake, location_t *fruit, int *direct)
{
	control(direct);
	update_snake(snake, fruit, *direct);
	show_game_scene(snake, *fruit);
	sleep(1);
}

int is_eat_fruit(const object_t *snake, location_t fruit)
{
	return ((snake[0].location.x == fruit.x) && (snake[0].location.y == fruit.y));
}

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

void control(int *direct)
{
	if(kbhit())
	{
		char c = getch();
		switch(c)
		{
			case 'w':
			case 'W':
				*direct = UP;
				break;
			case 'a':
			case 'A':
				*direct = LEFT;
				break;
			case 's':
			case 'S':
				*direct = DOWN;
				break;
			case 'd':
			case 'D':
				*direct = RIGHT;
			default:
				break;
		}

	}
}

void update_snake(object_t *snake, location_t *fruit, int direct)
{

	location_t *snakePointLocation = &(snake[0].location);
	int prevX = snake[0].location.x;
	int prevY = snake[0].location.y;
	
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

	//NEED BEBUG
	//first, save old location -> prev
	//next, save location of next snake point -> done
	//finally, set next snake point to old location

	
	while(i < MAX_LENGTH_SNAKE && snake[i].isExist)
	{
		
		prev2X = snake[i].location.x; 
		prev2Y = snake[i].location.y;		
		
		snake[i].location.x = prevX;
		snake[i].location.y = prevY;

		prevX = prev2X;
		prevY = prev2Y;
		i++;
	}

	if(is_eat_fruit(snake, *fruit))
	{
		snake[i].isExist = TRUE;
		snake[i].location.x = prevX;
		snake[i].location.y = prevY;
		set_fruit(fruit);
	}
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
}