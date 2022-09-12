HEADERS = PC.h Weapon.h Class.h Spell.h
OBJECTS = Combat.o PC.o Weapon.o Class.o Spell.o

Combat : $(OBJECTS)
	g++ -std=c++17 -Wall -o Combat $(OBJECTS)

Combat.o : Combat.cpp $(HEADERS)
	g++ -std=c++17 -Wall -c Combat.cpp

PC.o : PC.cpp $(HEADERS)
	g++ -std=c++17 -Wall -c PC.cpp
    
Weapon.o : Weapon.cpp $(HEADERS)
	g++ -std=c++17 -Wall -c Weapon.cpp
    
Class.o : Class.cpp $(HEADERS)
	g++ -std=c++17 -Wall -c Class.cpp

Spell.o : Spell.cpp $(HEADERS)
	g++ -std=c++17 -Wall -c Spell.cpp

clean :
	rm -f Combat.exe *.o