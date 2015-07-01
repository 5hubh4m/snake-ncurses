class Snake {
	std::deque<Cell> cells;
	std::deque<Node> nodes;
	int fdir, bdir;
public:
	Snake() {
		int i;
		Cell temp;
		fdir=bdir=RIGHT;
		temp.p.row=0;
		temp.c='@';
		for(i=0; i<DEF_LEN_FUN-1; i++) {
			temp.p.col=i;
			cells.push_front(temp);
		}
		temp.c='O';
		temp.p.col=i;
		cells.push_front(temp);
	}
	void createNode(int d) {
		fdir=d;
		Node n;
		n.p.row=cells.front().p.row;
		n.p.col=cells.front().p.col;
		n.dir=d;
		nodes.push_back(n);
	}
	void render(void) {
		int row, col;
		row=cells.front().p.row;
		col=cells.front().p.col;
		erase();
		for(std::deque<Cell>::iterator it=cells.begin(); it!=cells.end(); ++it){
			mvaddch(it->p.row, it->p.col, it->c);
		}
		refresh();
	}
	void movesnake(void) {
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
				bdir=nodes.front().dir;
				nodes.pop_front();
			}
		}
		cells.pop_back();
		switch(bdir) {
			case UP:
				cells.back().p.row=getrow(cells.back().p.row-1);
				break;
			case DOWN:
				cells.back().p.row=getrow(cells.back().p.row+1);
				break;
			case RIGHT:
				cells.back().p.col=getcol(cells.back().p.col+1);
				break;
			case LEFT:
				cells.back().p.col=getcol(cells.back().p.col-1);
				break;
		}
	}
	int getfdir(void) {
		return fdir;
	}
	int getbdir(void) {
		return bdir;
	}
	void setfdir(int dir) {
		fdir=dir;
	}
	void setbdir(int dir) {
		bdir=dir;
	}
};

class Classic_Snake {
	std::deque<Cell> cells;
	std::deque<Node> nodes;
	int fdir, bdir;
	int score, coll;
	Treat T;
public:
	Classic_Snake() {
		int i;
		Cell temp;
		fdir=bdir=RIGHT;
		temp.p.row=0;
		temp.c='@';
		for(i=0; i<DEF_LEN_CLASSIC-1; i++) {
			temp.p.col=i;
			cells.push_front(temp);
		}
		temp.c='O';
		temp.p.col=i;
		cells.push_front(temp);
		T.p.row=12;
		T.p.col=39;
		T.points=1;
		T.c='&';
		score=0;
		coll=0;
	}
	void createNode(int d) {
		fdir=d;
		Node n;
		n.p.row=cells.front().p.row;
		n.p.col=cells.front().p.col;
		n.dir=d;
		nodes.push_back(n);
	}
	void addtreat(void) {
		T.p=rand_point(cells);
		T.points=rand_score();
		T.c=rand_char();
	}
	void movesnake(void) {
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
					bdir=nodes.front().dir;
					nodes.pop_front();
				}
			}
			cells.pop_back();
			switch(bdir) {
				case UP:
					cells.back().p.row=getrow(cells.back().p.row-1);
					break;
				case DOWN:
					cells.back().p.row=getrow(cells.back().p.row+1);
					break;
				case RIGHT:
					cells.back().p.col=getcol(cells.back().p.col+1);
					break;
				case LEFT:
					cells.back().p.col=getcol(cells.back().p.col-1);
					break;
			}
		}
		else {
			score+=T.points;
			addtreat();
		}
	}
	void render(void) {
		int row, col;
		row=cells.front().p.row;
		col=cells.front().p.col;
		erase();
		for(std::deque<Cell>::iterator it=cells.begin(); it!=cells.end(); ++it){
			mvaddch(it->p.row, it->p.col, it->c);
		}
		mvaddch(T.p.row, T.p.col, T.c);
		refresh();
	}
	int collide(void) {
		for(std::deque<Cell>::iterator it=cells.begin(); it!=cells.end(); ++it){
			if(cells.front().p.row==it->p.row && cells.front().p.col==it->p.col && it!=cells.begin()) {
				return 1;
			}
		}
		return 0;
	}
	int getscore(void) {
		return score;
	}
	int getcoll(void) {
		return coll;
	}
	int getfdir(void) {
		return fdir;
	}
	int getbdir(void) {
		return bdir;
	}
	void setfdir(int dir) {
		fdir=dir;
	}
	void setbdir(int dir) {
		bdir=dir;
	}
};

class Score {
	int scores[14];
	int head;
public:
	Score() {
		head=-1;
		for(int i=0; i<14; i++) {
			scores[i]=-1;
		}
	}
	void filewrite() {
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
	void fileread() {
		std::ifstream file;
		file.open(FILE_NAME, std::ios::in | std::ios::binary);
		if(file.is_open()) {
			file.read((char *)this, sizeof(Score));
		}
		file.close();
		sortscore();
	}
	void addscore(int s) {
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
	void sortscore(void) {
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
	void showscores(void) {
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
	int gethead(void) {
		return head;
	}
};