all: main

NAME = ecs

OBJECTS = example.o glad.o Engine.o EntityManager.o

INC = -Iinc

CC = g++-13

CXX_FLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -std=c++20

main: $(OBJECTS)
	$(CC) $^ $(CXX_FLAGS) $(INC) -O3 -o $(NAME)

%.o: src/%.c
	$(CC) -c $< $(INC) -o $@

%.o: src/%.cpp
	$(CC) -c $< $(INC) -o $@

realclean: $(OBJECTS) $(NAME)
	rm $^

clean: $(NAME)
	rm $<
