/************************************************************************
    > File Name: Board.cpp
    > Author: huang
    > Mail: 13100937921@163.com 
    > Created Time: 2019年07月21日 星期日 13时15分42秒
************************************************************************/
#include "Board.h"
#include "Piece.h"
Board::Board(int rows, int cols) : rows_(rows), cols_(cols) {

}

bool Board::isFree(Position& position) const {
	return !pieces_.count(position);
}

PiecePtr Board::getPieceOnBoard(Position& position) {
	return pieces_[position];
}

void Board::wipePieceOnBoard(Position& position) {
	std::unordered_map<Position, PiecePtr, PositionHashNode>::iterator it = pieces_.find(position);
	//it->second->setState(DEAD);
	pieces_.erase(it);
}

void Board::placePieceOnBoard(PiecePtr& piece) {
	piece->setState(ONBOARD);
	pieces_[piece->getPosition()] = piece;
}

ChessBoard::ChessBoard() : Board(CHESS_ROWS, CHESS_COLS) {
	
}

GoBoard::GoBoard() : Board(GO_ROWS, GO_COLS) {

}

bool ChessBoard::isInBounds(Position& position) const {
	return (position.x_ <= rows_) && (position.y_ <= cols_);	
}

bool GoBoard::isInBounds(Position& position) const {
	return (position.x_ < rows_) && (position.y_ < cols_);
}

BoardPtr BoardFactory::boardPtr = BoardPtr();

BoardPtr BoardFactory::getBoard(GameType type) {
	if (!boardPtr) {
		if (type == CHESS) {
			boardPtr = std::make_shared<ChessBoard>();
		}
		else {
			boardPtr = std::make_shared<GoBoard>();
		}
	}
	return boardPtr;
}