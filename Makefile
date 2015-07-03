CC = g++
CFLAGS = -Wall -std=c++11
#INCLUDES =
#LFLAGS =
LIBS = -lncurses
SRCS = main.cpp snake.cpp score.cpp snake_ncurses.cpp
OBJS = $(SRCS:.cpp=.o)
MAIN = snake_ncurses

.PHONY : depend clean

all : $(MAIN)
	@echo snake_ncurses compiled and linked

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

c.o :
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean :
	$(RM) *.o *~ $(MAIN) *db

run :
	./$(MAIN)

depend : $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
