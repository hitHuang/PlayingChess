/************************************************************************
    > File Name: Board.h
    > Author: huang
    > Mail: 13100937921@163.com 
    > Created Time: 2019年07月21日 星期日 08时52分33秒
************************************************************************/
#ifndef BOARD_H
#define BOARD_H

#include <unordered_map>
#include <memory>
#include "types.h"
#include "Position.h"

#define CHESS_ROWS 18
#define CHESS_COLS 18
#define GO_ROWS 8
#define GO_COLS 8

class Game;
class Piece;
class Board;
typedef std::shared_ptr<Piece> PiecePtr;
typedef std::shared_ptr<Board> BoardPtr;

class Board {
public:
	Board(int rows, int cols);
	Board(const Board&) = delete;
	Board& operator=(const Board&) = delete;

public:
//为了能够实例化子对象Board，原本设为纯虚函数才好
	virtual bool isInBounds(Position& position) const { return true; };
	bool isFree(Position& position) const ;
//ps:为了避免冗余，以下函数不进行安全检查，由调用方保证调用安全
	//因为Piece中有position信息，所以不需额外提供位置
	PiecePtr getPieceOnBoard(Position& position) ;
	void placePieceOnBoard(PiecePtr& piece);
	void wipePieceOnBoard(Position& position);

protected:
	const int	rows_;
	const int	cols_;
//Board类中保存piece的shared指针
	std::unordered_map<Position, PiecePtr, PositionHashNode> pieces_;
};

class ChessBoard : public Board {
public:
	ChessBoard();

public:
	virtual bool isInBounds(Position& position) const override;
};

class GoBoard : public Board {
public:
	GoBoard();

public:
	virtual bool isInBounds(Position& position) const override;
};

//Board工厂类，实际上是单例
class BoardFactory {
public:
	static BoardPtr getBoard(GameType type);

private:
	static BoardPtr boardPtr;
};

#endif
