/************************************************************************
    > File Name: Action.h
    > Author: huang
    > Mail: 13100937921@163.com 
    > Created Time: 2019年07月21日 星期日 08时53分05秒
************************************************************************/
#ifndef ACTION_H
#define ACTION_H
#include <memory>
#include <utility>
class Game;
class Board;
class Piece;
class Player;
class Position;

class Action {
public:
	typedef std::shared_ptr<Piece>  PiecePtr;
	typedef std::shared_ptr<Board>  BoardPtr;
	typedef std::shared_ptr<Player> PlayerPtr;
	typedef std::shared_ptr<Game> 	GamePtr;
public:
	Action(Game* game) : game_(game) { }
	Action(const Action&) = delete;
	Action& operator=(const Action&) = delete;
public:
//指定Action操作的Board对象
	void setBoard(BoardPtr& board) { board_ = board; }

public:
	bool place(Position& position);
	bool move(Position& position1, Position& position2);
	bool wipe(Position& position);
	bool eat(Position& position1, Position& position2);
	PiecePtr query(Position& postion);
	std::pair<int, int> stat();

private:
	Game* game_;
	BoardPtr board_;
};

#endif
