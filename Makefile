all:
	g++ -c funciones.cpp
	g++ -c menu.cpp
	g++ -o ejecutable funciones.o menu.o
	del *.o
	./ejecutable
