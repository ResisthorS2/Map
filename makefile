menu: menu.o
	g++ -o menu menu.o

menu.o: ./src/menu.cpp
	g++ -c ./src/menu.cpp

