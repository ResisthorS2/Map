menu: menu.o
	gpp -o menu menu.o

menu.o: menu.cpp
	gpp -c menu.cpp

