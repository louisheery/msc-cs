OBJ = main.o plugboard.o reflector.o rotor.o enigma.o utilities.o
EXE = enigma
CXX = g++
CPPFLAGS = -Wall -g

$(EXE): $(OBJ)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $(EXE)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $<

main.o: enigma.hpp errors.h utilities.hpp
utilities.o: utilities.hpp errors.h
plugboard.o: plugboard.hpp enigma.hpp errors.h utilities.hpp
reflector.o: reflector.hpp enigma.hpp errors.h utilities.hpp
rotor.o: rotor.hpp enigma.hpp errors.h utilities.hpp
enigma.o: enigma.hpp errors.h utilities.hpp

clean:
	rm -f *.o
