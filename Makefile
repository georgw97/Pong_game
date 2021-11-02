all: compile link

compile:
	g++ -I src/include -c main.cpp -c funcs.cpp
link:
	g++ main.o funcs.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system