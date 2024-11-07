NAME = main

all: $(NAME)

OBJECTS = Engine.o glad.o $(NAME).o EntityManager.o ComponentManager.o Ecs.o

INC = inc

DEFINE = DEBUG
#DEFINE = 

CC = g++-11

LINK = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

CXX_FLAGS = -std=c++20

$(NAME): $(OBJECTS)
	$(CC) $^ $(LINK) -O3 -o $(NAME)

%.o: src/%.c
	$(CC) $^ -I$(INC) -D$(DEFINE) $(CXX_FLAGS) -c -o $@

%.o: src/%.cpp
	$(CC) $^ -I$(INC) -D$(DEFINE) $(CXX_FLAGS) -c -o $@

realclean: $(OBJECTS) $(NAME)
	rm $^

clean: $(NAME)
	rm $<
