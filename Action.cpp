/************************************************************************
    > File Name: Action.cpp
    > Author: huang
    > Mail: moon7921@163.com 
    > Created Time: 2019年07月21日 星期日 22时01分11秒
************************************************************************/
#include "Action.h"
#include "Game.h"
#include "Board.h"
#include "Piece.h"
#include "Player.h"
#include "Position.h"

bool Action::place(Game* game_, Position& position) {
	if (game_->getType() == GO) return false;
	BoardPtr board_ = game_->getBoard();
	if (!board_->isInBounds(position))	return false;
	if (!board_->isFree(position))	return false;
	PlayerPtr player = game_->getTurn();
	ColorType color;
	if (player->getType() == PLAYER1) color = WHITE;
	else	color = BLACK;
	PiecePtr piece = PieceFactory::getPiece(player, color);
	piece->setState(ONBOARD);
	piece->setPosition(position);
	board_->placePieceOnBoard(piece);
	game_->addPiece(piece);
	return true;
}

bool Action::wipe(Game* game_, Position& position) {
	if (game_->getType() == GO)	return false;
	BoardPtr board_ = game_->getBoard();
	if (!board_->isInBounds(position))	return false;
	if (board_->isFree(position))	return false;
	PiecePtr piece = board_->getPieceOnBoard(position);
	if (piece->getOwner() == game_->getTurn()) return false;
	board_->wipePieceOnBoard(position);
	game_->delPiece(piece);
	return true;
}

bool Action::move(Game* game_, Position& position1, Position& position2) {
	if (game_->getType() == CHESS)	return false;
	BoardPtr board_ = game_->getBoard();
	if (!board_->isInBounds(position1) || !board_->isInBounds(position2))	return false;
	if (position1 == position2)	return false;
	if (board_->isFree(position1) || !(board_->isFree(position2)))	return false;
	PiecePtr piece = board_->getPieceOnBoard(position1);
	if (piece->getOwner() != game_->getTurn())	return false;
	board_->wipePieceOnBoard(position1);
	piece->setPosition(position2);
	board_->placePieceOnBoard(piece);
	return true;
}

bool Action::eat(Game* game_, Position& position1, Position& position2) {
	if (game_->getType() == CHESS)	return false;
	BoardPtr board_ = game_->getBoard();
	if (!board_->isInBounds(position1) || !board_->isInBounds(position2))	return false;
	if (position1 == position2)	return false;
	if (board_->isFree(position1) || board_->isFree(position2))	return false;
	PiecePtr piece1 = board_->getPieceOnBoard(position1);
	PiecePtr piece2 = board_->getPieceOnBoard(position2);
	if (piece1->getOwner() != game_->getTurn()) return false;
	if (piece2->getOwner() == game_->getTurn()) return false;
	board_->wipePieceOnBoard(position2);
	board_->wipePieceOnBoard(position1);
	piece1->setPosition(position2);
	board_->placePieceOnBoard(piece1);
	game_->delPiece(piece2);
	return true;
}

PiecePtr Action::query(Game* game_, Position& position) {
	BoardPtr board_ = game_->getBoard();
	if (board_->isFree(position)) {
		return PiecePtr();
	}
	else {
		PiecePtr piece = board_->getPieceOnBoard(position);
		return piece;
	}
}

std::pair<int, int> Action::stat(Game* game_) {
	int pieceNums1 = game_->getPieceNums(WHITE);
	int pieceNums2 = game_->getPieceNums(BLACK);
	return {pieceNums1, pieceNums2};
}