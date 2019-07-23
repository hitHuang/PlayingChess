/************************************************************************
    > File Name: Piece.cpp
    > Author: huang
    > Mail: moon7921@163.com 
    > Created Time: 2019年07月22日 星期一 13时51分47秒
************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include "Piece.h"
#include "Player.h"
#include "Position.h"

typedef std::shared_ptr<Piece> PiecePtr;

std::vector<std::string> colorStr  = {"white", "black"};
std::vector<std::string> stateStr  = {"init", "onboard", "dead"};
std::vector<std::string> roleStr   = {"norole", "king", "queen", "rook", 
									  "knight", "bishop", "pawn"};

std::ostream& operator<<(std::ostream& os, PiecePtr& piece) {
	os << "owner: " << piece->getOwner()->getName() << "  |  ";
	os << "color: " << colorStr[static_cast<int>(piece->getColor())] << "  |  ";
	os << "role: " << roleStr[static_cast<int>(piece->getRole())] << "  |  ";
	os << "state: " << stateStr[static_cast<int>(piece->getState())] << "  |  ";
	os << "position: " << piece->getPosition();
	return os;
}