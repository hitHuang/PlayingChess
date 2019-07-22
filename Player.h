/************************************************************************
    > File Name: Player.h
    > Author: huang
    > Mail: 13100937921@163.com 
    > Created Time: 2019年07月21日 星期日 08时52分52秒
************************************************************************/
#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "types.h"

class Player {
public:
	Player(std::string& name) : name_(name){
			++count_;
			if (count_ == 1) type_ = PLAYER1;
			else if (count_ == 2) type_ = PLAYER2;
			else throw;
	}
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;

public:
	PlayerType getType() const { return type_; }
	std::string getName() const { return name_; }

private:
	PlayerType  type_;
	std::string name_;
	static int  count_;
};

#endif
