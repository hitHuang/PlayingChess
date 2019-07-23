/************************************************************************
    > File Name: Game.cpp
    > Author: huang
    > Mail: moon7921@163.com 
    > Created Time: 2019年07月21日 星期日 10时59分26秒
************************************************************************/
#include <iostream>
#include <fstream>
#include "Game.h"
#include "Board.h"
#include "Piece.h"
#include "Player.h"
#include "Action.h"
#include "Operation.h"
using std::cout;
using std::cin;
using std::endl;

//簿记
struct LOG {
	LOG(const char* file) : of_(std::ofstream(file)) {}
	~LOG() {
		of_.close();
	}
	LOG& operator<<(std::string& record) {
		of_ << record << "\n";
		return *this;
	}
private:
	std::ofstream of_;
};

int Player::count_ = 0;
GamePtr GameFactroy::game_ = GamePtr();

Game::Game(GameType type) : type_(type), state_(READY) {
	board_ = BoardFactory::getBoard(type_);
	setPlayer(std::cin, std::cout);
	setTurn(PLAYER1);
	//action_->setBoard(board_);
}

int Game::getPieceNums(ColorType type) const {
	if (type == WHITE)	return piecesW_.size();
	return piecesB_.size();
}

void Game::addPiece(PiecePtr& piece) {
	if (piece->getColor() == WHITE) {
		piecesW_.push_back(piece);
	}
	else {
		piecesB_.push_back(piece);
	}
}

void Game::delPiece(PiecePtr& piece) {
	if (piece->getColor() == WHITE) {
		delPieceW(piece);
	}
	else {
		delPieceB(piece);
	}
}

void Game::delPieceW(PiecePtr& piece) {
	std::vector<PiecePtr>::iterator it = piecesW_.begin();
	for ( ; it != piecesW_.end(); ++it) {
		if (*it == piece) {
			piecesW_.erase(it);
			break;
		}
	}
}

void Game::delPieceB(PiecePtr& piece) {
	std::vector<PiecePtr>::iterator it = piecesB_.begin();
	for ( ; it != piecesB_.end(); ++it) {
		if (*it == piece) {
			piecesB_.erase(it);
			break;
		}
	}
}

void Game::setTurn(PlayerType type) {
	whosTurn_ = type;
}

void Game::turn() {
	if (whosTurn_ == PLAYER1) {
		whosTurn_ = PLAYER2;
	}
	else {
		whosTurn_ = PLAYER1;
	}
}

PlayerPtr Game::getTurn() const {
	if (whosTurn_ == PLAYER1) {
		return player1_;
	}
	return player2_;
}

GameType Game::getType() const {
	return type_;
}

GameState Game::getState() const {
	return state_;
}

GameState Game::setState(GameState state) {
	state_ = state;
}

void Game::setPlayer(std::istream& is, std::ostream& os) {
	std::string name1("player1"), name2("player2");
	while (1) {
		os << "please input player1's name : ";
		is >> name1;
		os << "please input player2's name : ";
		is >> name2;
		if (name1.empty() || name2.empty()) {
			os << "name can't be null!!" << "\n";
		}
		else if (name1 == name2) {
			os << "name cant't be same!!" << "\n";
		}
		else {
			break;
		}
	}
	player1_ = std::make_shared<Player>(name1);
	player2_ = std::make_shared<Player>(name2);
}

void Game::start() {
	init();

	setState(RUNNING);

	Operation op;
	OpType command;
	PiecePtr queryRes;
	std::pair<int, int> statRes;
	bool execFlag;

	LOG Log("log.txt");
	cout << "game start :)" << endl;

	std::string record;//存放簿记内容

	while (getState() == RUNNING) {
		execFlag = false;
		std::string().swap(record);
		record += getTurn()->getName() + ": ";

		cout << record << ": ";
		op.readCommand();
#ifdef DEBUG_ON
		cout << op << endl;
#endif
		command = op.getType();
		Position position1 = op.getPosition1();
		Position position2 = op.getPosition2();
		switch (command) {
			case INVALID:
				cout << "this operation is invalid,try again :(" << endl;
				break;
			case END:
				setState(OVER);
				execFlag = true;
				cout << "game over!!" << endl;
				break;
			case YIELD:
				execFlag = true;
				turn();
				break;
			case PLACE:
				if (place(this, position1)) {
					execFlag = true;
					turn();
				}
				else {
					cout << "this operation is invalid,try again :("  << endl;
				}
				break;
			case MOVE:
				if (move(this, position1, position2)) {
					execFlag = true;
					turn();
				}
				else {
					cout << "this operation is invalid,try again :("  << endl;
				}
				break;
			case WIPE:
				if (wipe(this, position1)) {
					cout << "this operation is invalid,try again :("  << endl;
				}
				else {
					execFlag = true;
				}
				break;
			case EAT:
				if (eat(this, position1, position2)) {
					execFlag = true;
					turn();
				}
				else {
					cout << "this operation is invalid,try again :("  << endl;
				}
				break;
			case QUERY:
				queryRes = query(this, position1);
				if (!queryRes) {
					cout << "this position is free!!" << endl;
				} 
				else {
					cout << queryRes << endl;
				}
				break;
			case STAT:
				statRes = stat(this);
				cout << "white piece numbers : " << statRes.first << " | " << 
						"black piece numbers : " << statRes.second << endl;
				break;
			default:
				break;
		}
		if (execFlag) {
			record += op.toStr();
			Log << record;
		}
	}
}

ChessGame::ChessGame() : Game(CHESS) {

}

GoGame::GoGame() : Game(GO) {

}

void GoGame::init() {
	initPieces();
}

void GoGame::initPieces() {
	std::vector<RoleType> roleV = {KING, QUEEN, BISHOP, BISHOP, KNIGHT, KNIGHT, ROOK, ROOK,
									PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN};
	std::vector<std::pair<int, int>> posWV = {{0,3},{0,4},{0,2},{0,5},{0,1},{0,6},{0,0},{0,7},
												{1,0},{1,1},{1,2},{1,3},{1,4},{1,5},{1,6},{1,7}};
	std::vector<std::pair<int, int>> posBV = {{7,3},{7,4},{7,2},{7,5},{7,1},{7,6},{7,0},{7,7},
												{6,0},{6,1},{6,2},{6,3},{6,4},{6,5},{6,6},{6,7}};										
	for (int i = 0; i < 16; i++) {
		Position position(posWV[i]);
		piecesW_.push_back(PieceFactory::getPiece(player1_, WHITE, roleV[i], ONBOARD, position));
		board_->placePieceOnBoard(piecesW_[i]);
	}
	for (int i = 0; i < 16; i++) {
		Position position(posBV[i]);
		piecesB_.push_back(PieceFactory::getPiece(player2_, BLACK, roleV[i], ONBOARD, position));
		board_->placePieceOnBoard(piecesB_[i]);
	}
}


GamePtr GameFactroy::getGame() {
	if (!game_) {
		GameType type;
		std::string game_type;
		while ((game_type != "chess") && (game_type != "go")) {
			cout << "please input the game type (\"chess\" or \"go\") : ";
			cin >> game_type;
			if (game_type == "chess") {
				type = CHESS;
			}
			else if (game_type == "go") {
				type = GO;
			}
			else {
				cout << "no this type, try again :(" << endl;
			}
		}
		if (type == CHESS) {
			game_ = std::make_shared<ChessGame>();
		}
		else {
			game_ = std::make_shared<GoGame>();
		}
	}
	return game_;
}