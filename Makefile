# Makefile to compile the program 
# Author(s): Levi Shaffer & Joshua Lemon
# Course: COP 4634
# Project II

CXX = c++
CFLAGS = -std=c++11 -Wall 

main: spawner
	$(CXX) $(CFLAGS) -o mt-collatz -lpthread -lrt -pthread *.cpp 

spawner:
	$(CXX) $(CFLAGS) -c -o spawner.o CollatzSpawner.cpp

clean:
	$(RM) *.o *.gch core mt-collatz *.exe
