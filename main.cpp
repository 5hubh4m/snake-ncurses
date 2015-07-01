#include "snake_header.hpp"

int main(void) {
	int temp;
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
