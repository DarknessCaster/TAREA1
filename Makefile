all:
	g++ -c funciones.cpp
	g++ -c emisor.cpp
	g++ -o ejecutable funciones.o emisor.o
	del *.o
	./ejecutable
