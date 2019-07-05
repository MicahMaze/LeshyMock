CC=g++
CFLAGS=-std=c++11 -Wall
INC=-I../Main

TESTS=\
TestMocks \

TestMocks: TestMocks.cpp 
	$(CC) $(CFLAGS) -o $@ $^ $(INC)

clean:
	rm -rf *.o $(TESTS)