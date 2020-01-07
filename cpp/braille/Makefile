braille: main.o braille.o
	g++ -g main.o braille.o -o braille

main.o: main.cpp braille.h
	g++ -Wall -g -c main.cpp

braille.o: braille.cpp braille.h
	g++ -Wall -g -c braille.cpp

clean:
	rm -f *.o braille