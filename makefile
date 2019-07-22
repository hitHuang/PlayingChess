all:test
test:test.o Game.o Board.o Position.o Piece.o Action.o Operation.o
	g++ -g -o test test.cpp Game.cpp Board.cpp Position.o Piece.o Action.o Operation.cpp
test.o:test.cpp
	g++ -g -c test.cpp
Game.o:Game.cpp Game.h
	g++ -g -c Game.cpp
Board.o:Board.cpp Board.h
	g++ -g -c Board.cpp
Position.o:Position.cpp Position.h
	g++ -g -c Position.cpp
Piece.o:Piece.cpp Piece.h
	g++ -g -c Piece.cpp
Action.o:Action.cpp Action.h
	g++ -g -c Action.cpp
Operation.o:Operation.cpp Operation.h
	g++ -g -c Operation.cpp
.PHONY clean:
	rm -f *.o
