#include <queue>
#include <cstdlib>
#include <ncurses.h>
#include <ctime>
#include <fstream>
#include <iostream>

#include "snake_ncurses.hpp"
#include "snake.hpp"
#include "score.hpp"

Snake::Snake(int len) {
	int i;
	Cell temp;
	fdir=RIGHT;
	temp.p.row=0;
	temp.c='@';
	for(i=0; i<len-1; i++) {
		temp.p.col=i;
		cells.push_front(temp);
	}
	temp.c='O';
	temp.p.col=i;
	cells.push_front(temp);
}

void Snake::createNode(int d) {
		fdir=d;
		Node n;
		n.p.row=cells.front().p.row;
		n.p.col=cells.front().p.col;
		n.dir=d;
		nodes.push_back(n);
	}

void Snake::render(void) {
		erase();
		for(std::deque<Cell>::iterator it=cells.begin(); it!=cells.end(); ++it){
			mvaddch(it->p.row, it->p.col, it->c);
		}
		refresh();
	}

void Snake::movesnake(void) {
		Point f, b;
		Cell temp;
		f=cells.front().p;
		b=cells.back().p;
		cells.front().c='@';
		switch(fdir) {
			case UP:
				f.row=getrow(f.row-1);
				break;
			case DOWN:
				f.row=getrow(f.row+1);
				break;
			case RIGHT:
				f.col=getcol(f.col+1);
				break;
			case LEFT:
				f.col=getcol(f.col-1);
				break;
		}
		temp.p=f;
		temp.c='O';
		cells.push_front(temp);
		if(!nodes.empty()) {
			if(b.row==nodes.front().p.row && b.col==nodes.front().p.col) {
				nodes.pop_front();
			}
		}
		cells.pop_back();
}

int Snake::getfdir(void) {
		return fdir;
}

void Snake::setfdir(int dir) {
		fdir=dir;
}

Classic_Snake::Classic_Snake():Snake(2) {
	T.p.row=12;
	T.p.col=39;
	T.points=1;
	T.c='&';
	score=0;
	coll=0;
}

void Classic_Snake::addtreat(void) {
	T.p=rand_point(cells);
	T.points=rand_score();
	T.c=rand_char();
}

void Classic_Snake::movesnake(void) {
	Point f, b;
	Cell temp;
	f=cells.front().p;
	b=cells.back().p;
	cells.front().c='@';
	switch(fdir) {
		case UP:
			f.row=getrow(f.row-1);
			break;
		case DOWN:
			f.row=getrow(f.row+1);
			break;
		case RIGHT:
			f.col=getcol(f.col+1);
			break;
		case LEFT:
			f.col=getcol(f.col-1);
			break;
	}
	temp.p=f;
	temp.c='O';
	cells.push_front(temp);
	if(collide()) {
		coll=1;
		return;
	}
	if(cells.front().p.row!=T.p.row || cells.front().p.col!=T.p.col) {
		if(!nodes.empty()) {
			if(b.row==nodes.front().p.row && b.col==nodes.front().p.col) {
				nodes.pop_front();
			}
		}
		cells.pop_back();
	}
	else {
		score+=T.points;
		addtreat();
	}
}

void Classic_Snake::render(void) {
	erase();
	for(std::deque<Cell>::iterator it=cells.begin(); it!=cells.end(); ++it){
		mvaddch(it->p.row, it->p.col, it->c);
	}
	mvaddch(T.p.row, T.p.col, T.c);
	refresh();
}

int Classic_Snake::collide(void) {
	for(std::deque<Cell>::iterator it=cells.begin(); it!=cells.end(); ++it){
		if(cells.front().p.row==it->p.row && cells.front().p.col==it->p.col && it!=cells.begin()) {
			return 1;
		}
	}
	return 0;
}

int Classic_Snake::getcoll(void) {
	return coll;
}

int Classic_Snake::getscore(void) {
	return score;
}
