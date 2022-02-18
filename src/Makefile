CC = g++ 
CFLAGS = -std=c++17 -c -g -Og -Wall -pedantic
OBJ = main.o CelestialBody.o
DEPS = main.cpp CelestialBody.cpp CelestialBody.hpp
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
EXE = SS_simulation

all: $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm $(OBJ) $(EXE)
