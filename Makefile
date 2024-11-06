all: main

NAME = ecs

OBJECTS = example.o glad.o Engine.o EntityManager.o ComponentManager.o

INC = -Iinc

DEFINE = DEBUG
#DEFINE = 

CC = g++-13

CXX_FLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -std=c++20

main: $(OBJECTS)
	$(CC) $^ $(CXX_FLAGS) $(INC) -O3 -o $(NAME)

%.o: src/%.c
	$(CC) -c $< $(INC) -o $@

%.o: src/%.cpp
	$(CC) -c $< $(INC) -D$(DEFINE) -o $@

realclean: $(OBJECTS) $(NAME)
	rm $^

clean: $(NAME)
	rm $<
