COMP=g++

SRC=src/main.cpp src/Cards.cpp

FLAG=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all:
	$(COMP) $(SRC) -o app $(FLAG)