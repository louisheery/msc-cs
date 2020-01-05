words: main.o words.o
	g++ -g main.o words.o -o words

main.o: main.cpp words.h
	g++ -Wall -g -c main.cpp

words.o: words.cpp words.h
	g++ -Wall -g -c words.cpp

clean:
	rm -f *.o words