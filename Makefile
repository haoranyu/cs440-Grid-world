NAME_OF_EXECUTABLE_FILE = learning

COMPILER = g++
COMPILER_OPTS = -c -g


LINKER = g++
LINKER_OPTS = -o $(NAME_OF_EXECUTABLE_FILE)


OBJS = main.o maze.o state.o agent.o


#  linking the program.

$(NAME_OF_EXECUTABLE_FILE) : $(OBJS)
	$(LINKER) $(LINKER_OPTS) $(OBJS)

# Rules for performing the compilation of each individual object file.


maze.o : maze.h maze.cpp
	$(COMPILER) $(COMPILER_OPTS) maze.cpp
state.o : state.h state.cpp
	$(COMPILER) $(COMPILER_OPTS) state.cpp
agent.o : agent.h agent.cpp
	$(COMPILER) $(COMPILER_OPTS) agent.cpp


main.o : main.cpp maze.o state.o agent.o
	$(COMPILER) $(COMPILER_OPTS) main.cpp

clean:
	-rm *.o $(NAME_OF_EXECUTABLE_FILE)


