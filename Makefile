all: build

build:
	@echo "Construyendo..."
	g++ -c funciones.cpp
	g++ -c main.cpp
	g++ funciones.o main.o -o main
	.\main.exe

clean:
	rm *.o
	rm *.exe

clean_o:
	rm *.o

clean_exe:
	rm *.exe