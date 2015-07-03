#ifndef SNAKE_NCURSES_HPP
#define SNAKE_NCURSES_HPP

#define MAX_ROW 18
#define MAX_COL 79
#define DEF_LEN_FUN 25
#define DEF_LEN_CLASSIC 5

#define FILE_NAME "snake.db"

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define TIMEOUT 100
#define TIMEOUT_GAME_OVER 100000
#define TIMEOUT_LONG 10000

struct Point{
	int row, col;
};

struct Node {
	Point p;
	int dir;
};

struct Cell {
	Point p;
	char c;
};

struct Treat {
	Point p;
	int points;
	char c;
};

void print_snake(void);
int show_menu(void);
void show_gameover(int);
void fun_snake_game(void);
Point rand_point(std::deque<Cell>);
int rand_score(void);
char rand_char(void);
int getrow(int);
int getcol(int);
int diff(int, int);
int classic_game(void);

#endif
