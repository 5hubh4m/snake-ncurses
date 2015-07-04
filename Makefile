CC = gcc
CXX = g++
CXXFLAGS = -Wall -std=c++11
INCLUDES =
LFLAGS =
LIBS = -lncurses
SRCS = main.cpp snake.cpp score.cpp snake_ncurses.cpp
OBJS = $(SRCS:.cpp=.o)
MAIN = snake_ncurses

.PHONY : depend clean

all : $(MAIN)
	@echo snake_ncurses compiled and linked

$(MAIN) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

%o : %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<  -o $@

clean :
	$(RM) *.o *~ $(MAIN) *db

run :
	./$(MAIN)

depend : $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
