main: Funkcijos.o
	g++ -o main OOP5.cpp Functions.o
funkcijos:
	g++ -c Functions.cpp
clean:
	rm *.o main