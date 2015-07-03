#include <queue>
#include <cstdlib>
#include <ncurses.h>
#include <ctime>
#include <fstream>
#include <iostream>

#include "snake_ncurses.hpp"
#include "snake.hpp"
#include "score.hpp"

int main(void) {
	Score S;
	S.fileread();
	int ch;
	while(1) {
		ch=show_menu();
		switch(ch) {
			case 1:
				S.addscore(classic_game());
				break;
			case 2:
				fun_snake_game();
				break;
			case 3:
				S.showscores();
				break;
			case 4:
				S.filewrite();
				endwin();
				return 0;
		}
	}
}
