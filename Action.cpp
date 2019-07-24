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

bool Action::place(Game* game, Position& position) {
	if (game->getType() == GO) return false;
	BoardPtr board = game->getBoard();
	if (!board->isInBounds(position))	return false;
	if (!board->isFree(position))	return false;
	PlayerPtr player = game->getTurn();
	ColorType color;
	if (player->getType() == PLAYER1) color = WHITE;
	else	color = BLACK;
	PiecePtr piece = PieceFactory::getPiece(player, color);
	piece->setState(ONBOARD);
	piece->setPosition(position);
	board->placePieceOnBoard(piece);
	game->addPiece(piece);
	return true;
}

bool Action::wipe(Game* game, Position& position) {
	if (game->getType() == GO)	return false;
	BoardPtr board = game->getBoard();
	if (!board->isInBounds(position))	return false;
	if (board->isFree(position))	return false;
	PiecePtr piece = board->getPieceOnBoard(position);
	if (piece->getOwner() == game->getTurn()) return false;
	board->wipePieceOnBoard(position);
	game->delPiece(piece);
	return true;
}

bool Action::move(Game* game, Position& position1, Position& position2) {
	if (game->getType() == CHESS)	return false;
	BoardPtr board = game->getBoard();
	if (!board->isInBounds(position1) || !board->isInBounds(position2))	return false;
	if (position1 == position2)	return false;
	if (board->isFree(position1) || !(board->isFree(position2)))	return false;
	PiecePtr piece = board->getPieceOnBoard(position1);
	if (piece->getOwner() != game->getTurn())	return false;
	board->wipePieceOnBoard(position1);
	piece->setPosition(position2);
	board->placePieceOnBoard(piece);
	return true;
}

bool Action::eat(Game* game, Position& position1, Position& position2) {
	if (game->getType() == CHESS)	return false;
	BoardPtr board = game->getBoard();
	if (!board->isInBounds(position1) || !board->isInBounds(position2))	return false;
	if (position1 == position2)	return false;
	if (board->isFree(position1) || board->isFree(position2))	return false;
	PiecePtr piece1 = board->getPieceOnBoard(position1);
	PiecePtr piece2 = board->getPieceOnBoard(position2);
	if (piece1->getOwner() != game->getTurn()) return false;
	if (piece2->getOwner() == game->getTurn()) return false;
	board->wipePieceOnBoard(position2);
	board->wipePieceOnBoard(position1);
	piece1->setPosition(position2);
	board->placePieceOnBoard(piece1);
	game->delPiece(piece2);
	return true;
}

PiecePtr Action::query(Game* game, Position& position) {
	BoardPtr board = game->getBoard();
	if (board->isFree(position)) {
		return PiecePtr();
	}
	else {
		PiecePtr piece = board->getPieceOnBoard(position);
		return piece;
	}
}

std::pair<int, int> Action::stat(Game* game) {
	int pieceNums1 = game->getPieceNums(WHITE);
	int pieceNums2 = game->getPieceNums(BLACK);
	return {pieceNums1, pieceNums2};
}