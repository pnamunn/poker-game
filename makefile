.PHONY : clean
OBJECTS = main.o Card.o Dealer.o Deck.o Player.o PlayerList.o


# Executable
main : $(OBJECTS) helpers.h
	g++ $(OBJECTS) helpers.h -o main

# Objects
main.o : main.cpp
	g++ -c main.cpp

Card.o : Card.cpp Card.h
	g++ -c Card.cpp

Dealer.o : Dealer.cpp Dealer.h
	g++ -c Dealer.cpp

Deck.o : Deck.cpp Deck.h
	g++ -c Deck.cpp

Player.o : Player.cpp Player.h
	g++ -c Player.cpp

PlayerList.o : PlayerList.cpp PlayerList.h
	g++ -c PlayerList.cpp

clean :
	ifeq( $(OS), Windows_NT )
		del main.exe $(OBJECTS)
	else
		rm main $(OBJECTS)
	endif
