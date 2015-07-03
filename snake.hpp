#ifndef SNAKE_HPP
#define SNAKE_HPP

class Snake {
protected:
	std::deque<Cell> cells;
	std::deque<Node> nodes;
	int fdir;
public:
	Snake(int len=DEF_LEN_FUN);
	void createNode(int d);
	virtual void render(void);
	virtual void movesnake(void);
	int getfdir(void);
	void setfdir(int);
};

class Classic_Snake:public Snake {
protected:
	int score, coll;
	Treat T;
public:
	Classic_Snake();
	void addtreat(void);
	virtual void movesnake(void);
	virtual void render(void);
	int collide(void);
	int getscore(void);
	int getcoll(void);
};

#endif
