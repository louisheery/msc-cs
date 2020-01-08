stamp: main.o stamp.o
	g++ -g main.o stamp.o -lcrypto -o stamp

main.o: main.cpp stamp.h
	g++ -Wall -g -c -lcrypto main.cpp

stamp.o: stamp.cpp stamp.h
	g++ -Wall -g -c -lcrypto stamp.cpp

clean:
	rm -f *.o stamp