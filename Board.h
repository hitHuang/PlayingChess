/************************************************************************
    > File Name: Board.h
    > Author: huang
    > Mail: moon7921@163.com 
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
//原本应该设为纯虚函数，但为了在ChessBoard和GoBoard中能够实例化父类Board对象不得不如此
//有什么其他优雅的方法吗？？
	virtual bool isInBounds(Position& position) const { return true; };
	bool isFree(Position& position) const ;
//避免冗余，以下几个函数不进行安全检查，由调用方保证调用安全
	PiecePtr getPieceOnBoard(Position& position) ;
//为了支持Action，Board提供place和wipe最基本的操作，move和eat操作可以建立在这两个操作之上
//Piece中有position信息，不需额外提供位置
	void placePieceOnBoard(PiecePtr& piece);
	void wipePieceOnBoard(Position& position);

protected:
	const int	rows_;
	const int	cols_;
//Board类中保存piece的shared指针，用来方便的定位和操作Piece
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
