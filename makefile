CC=g++
CFLAGS= -std=c++1z
DEPS = Functions.h
OBJ = main.o Functions.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
