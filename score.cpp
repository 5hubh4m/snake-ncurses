#include <queue>
#include <cstdlib>
#include <ncurses.h>
#include <ctime>
#include <fstream>
#include <iostream>

#include "snake_ncurses.hpp"
#include "snake.hpp"
#include "score.hpp"

Score::Score() {
  head=-1;
  for(int i=0; i<14; i++) {
    scores[i]=-1;
  }
}

void Score::filewrite() {
  std::ofstream file;
  if(head>-1) {
    if(file.is_open()) {
      file.close();
    }
    file.open(FILE_NAME, std::ios::trunc | std::ios::binary);
    file.write((char *)this, sizeof(Score));
    file.close();
  }
}

void Score::fileread() {
  std::ifstream file;
  file.open(FILE_NAME, std::ios::in | std::ios::binary);
  if(file.is_open()) {
    file.read((char *)this, sizeof(Score));
  }
  file.close();
  sortscore();
}

void Score::addscore(int s) {
  sortscore();
  if(head<13) {
    scores[++head]=s;
    sortscore();
  }
  else {
    if(s>scores[0]) {
      scores[0]=s;
      sortscore();
    }
  }
}

void Score::sortscore(void) {
  int temp;
  if(head>0) {
    for(int i=0; i<=head; i++) {
      for(int j=0; j<=head-1; j++) {
        if(scores[j]>scores[j+1]) {
          temp=scores[j+1];
          scores[j+1]=scores[j];
          scores[j]=temp;
        }
      }
    }
  }
}

void Score::showscores(void) {
  sortscore();
  erase();
  int ch;
  int t=(23-head-1)/2;
  if(head>-1) {
    for(int i=head, j=0; i>=0; i--,  j++) {
      mvprintw(t+j, 36, "%2d. %2u", j+1, scores[i]);
    }
  }
  attron(A_STANDOUT);
  mvprintw(23, 25, "PRESS 'Q' to EXIT BACK TO MENU.");
  attroff(A_STANDOUT);
  refresh();
  while((ch=getch())!='q');
}

int Score::gethead(void) {
  return head;
}
