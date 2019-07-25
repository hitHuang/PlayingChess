/************************************************************************
    > File Name: Game.h
    > Author: huang
    > Mail: moon7921@163.com 
    > Created Time: 2019年07月21日 星期日 08时30分18秒
************************************************************************/

#ifndef GAME_H
#define GAME_H
#include <vector>
#include <memory>
#include <unordered_map>
#include "types.h"
#include "Action.h"

class Board;
class Piece;
class Player;

typedef std::shared_ptr<Game> GamePtr;

class Game : public Action {
public:
	Game(GameType type);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	typedef std::shared_ptr<Board>  BoardPtr;
	typedef std::shared_ptr<Piece>  PiecePtr;
	typedef std::shared_ptr<Player> PlayerPtr;
	typedef std::shared_ptr<Action> ActionPtr;

public:
	void start();

public:
	int getPieceNums(ColorType type) const ;
//增加一颗棋子
	void addPiece(PiecePtr& piece);
//删除一颗棋子
	void delPiece(PiecePtr& piece);
	void outAllPiecesInfo();

private:
	void delPieceW(PiecePtr& piece);
	void delPieceB(PiecePtr& piece);

public:
//每次有效action后切换到另一个player
	void setTurn(PlayerType type);
	PlayerPtr getTurn() const ;
	void turn();
	GameType getType() const ;
	GameState getState() const ;
	GameState setState(GameState state);

	BoardPtr getBoard() { return board_; }

protected:
//初始化player
	void setPlayer(std::istream& is, std::ostream& os);
	virtual void init() { }

protected:
	GameType type_;
	GameState state_;
	BoardPtr board_;
//当前＂存活＂的Piece
	std::vector<PiecePtr> piecesW_;
	std::vector<PiecePtr> piecesB_;
	PlayerPtr player1_;
	PlayerPtr player2_;
	PlayerType whosTurn_;
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
//国际象棋中初始化棋盘上的棋子
	void initPieces();
};

//包装Game的工厂类，实际上为单例
class GameFactroy{
public:
	static GamePtr getGame();
private:
	static GamePtr game_;
};

#endif
