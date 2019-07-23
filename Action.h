/************************************************************************
    > File Name: Action.h
    > Author: huang
    > Mail: moon7921@163.com 
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

//Action接口类
class Action {
public:
	typedef std::shared_ptr<Piece>  PiecePtr;
	typedef std::shared_ptr<Board>  BoardPtr;
	typedef std::shared_ptr<Player> PlayerPtr;
	typedef std::shared_ptr<Game> 	GamePtr;

public:
	bool place(Game* game_, Position& position);
	bool move(Game* game_, Position& position1, Position& position2);
	bool wipe(Game* game_, Position& position);
	bool eat(Game* game_, Position& position1, Position& position2);
	PiecePtr query(Game* game_, Position& postion);
	std::pair<int, int> stat(Game* game_);
};

#endif
