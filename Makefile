NAME = main

all: $(NAME)

OBJECTS = glad.o Engine.o EntityManager.o ComponentManager.o Ecs.o example.o

INC = -Iinc

DEFINE = DEBUG
#DEFINE = 

CC = g++-11

LINK = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -std=c++20

CXX_FLAGS = -std=c++20

main: $(OBJECTS)
	$(CC) $^ $(LINK) $(INC) -O3 -o $(NAME)

%.o: src/%.c
	$(CC) -c $< $(INC) -o $@

%.o: src/%.cpp
	$(CC) -c $< $(INC) -D$(DEFINE) $(CXX_FLAGS) -o $@

realclean: $(OBJECTS) $(NAME)
	rm $^

clean: $(NAME)
	rm $<
