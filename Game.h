/************************************************************************
    > File Name: Game.h
    > Author: huang
    > Mail: 13100937921@163.com 
    > Created Time: 2019年07月21日 星期日 08时30分18秒
************************************************************************/

#ifndef GAME_H
#define GAME_H
#include <vector>
#include <memory>
#include <unordered_map>
#include "types.h"

class Game;
class Board;
class Piece;
class Player;
class Action;

typedef std::shared_ptr<Game> GamePtr;

class Game {
public:
	Game(GameType type);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	typedef std::shared_ptr<Board>  BoardPtr;
	typedef std::shared_ptr<Piece>  PiecePtr;
	typedef std::shared_ptr<Player> PlayerPtr;
	typedef std::shared_ptr<Action> ActionPtr;

public:
	virtual void init() { }
	void start();

public:
	int getPieceNums(ColorType type) const ;
//增加一颗棋子
	void addPiece(PiecePtr& piece);
//删除一颗棋子
	void delPiece(PiecePtr& piece);

private:
	void delPieceW(PiecePtr& piece);
	void delPieceB(PiecePtr& piece);

public:
	void setTurn(PlayerType type);
	PlayerPtr getTurn() const ;
	void turn();
	GameType getType() const ;
	GameState getState() const ;
	GameState setState(GameState state);

protected:
//初始化时，从终端获取并设置player
	void setPlayer(std::istream& is, std::ostream& os);

//protected:
public:
	GameType type_;
	GameState state_;
	BoardPtr board_;
//国际象棋中的16颗白色和黑色棋子，围棋情况下初始为空
	std::vector<PiecePtr> piecesW_;
	std::vector<PiecePtr> piecesB_;
	PlayerPtr player1_;
	PlayerPtr player2_;
	PlayerType whosTurn_;
//动作
	ActionPtr action_;
};

class ChessGame : public Game {
public:
	ChessGame();
};

class GoGame : public Game {
public:
	GoGame();

public:
	virtual void init() override ;

private:
	void initPieces();
};

class GameFactroy{
public:
	static GamePtr getGame();
private:
	static GamePtr game_;
};

#endif
