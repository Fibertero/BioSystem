COMP=g++

SRC=src/main.cpp src/Camera.hpp

FLAG=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all:
	$(COMP) $(SRC) -o app $(FLAG)