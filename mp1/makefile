CC := g++
CFLAGS := -g -Wall
CXX = g++
CXXFLAGS = -std=c++1y -c -g -O0 -Wall -Wextra -pedantic
LD = g++
LDFLAGS = -std=c++1y   -lpthread -lm

main: main.o mp1.o PNG.o HSLAPixel.o lodepng.o
	$(CC) $(CFLAGS) main.o mp1.o PNG.o HSLAPixel.o lodepng.o -o main
mp1.o: mp1.cpp mp1.h
	$(CC) $(CFLAGS) -c mp1.cpp
main.o: main.cpp 
	$(CC) $(CFLAGS) -c main.cpp
PNG.o: cs225/PNG.cpp cs225/PNG.h
	$(CC) $(CFLAGS) -c cs225/PNG.cpp
HSLAPixel.o: cs225/HSLAPixel.cpp cs225/HSLAPixel.h
	$(CC) $(CFLAGS) -c cs225/HSLAPixel.cpp 
lodepng.o: cs225/lodepng/lodepng.cpp cs225/lodepng/lodepng.h
	$(CC) $(CFLAGS) -c cs225/lodepng/lodepng.cpp
test : unit_tests.o mp1.o PNG.o HSLAPixel.o lodepng.o
	$(LD) unit_tests.o mp1.o PNG.o HSLAPixel.o lodepng.o $(LDFLAGS) -o test
unit_tests.o : tests/unit_tests.cpp tests/catch.hpp cs225/PNG.h cs225/HSLAPixel.h
	$(CXX) $(CXXFLAGS) tests/unit_tests.cpp
clean :
	-rm -f *.o mp1