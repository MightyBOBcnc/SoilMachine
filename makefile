CC = g++-10 -std=c++20
CF = -Wfatal-errors -O3
LF = -I/usr/local/include -L/usr/local/lib

TINYLINK = -lX11 -lpthread -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lGL -lGLEW -lboost_system -lboost_filesystem

all: SoilMachine.cpp
			$(CC) SoilMachine.cpp $(CF) $(LF) -lTinyEngine $(TINYLINK) -o soilmachine
