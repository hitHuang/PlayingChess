/************************************************************************
    > File Name: test.cpp
    > Author: huang
    > Mail: moon7921@163.com 
    > Created Time: 2019年07月21日 星期日 09时38分16秒
************************************************************************/
#include <memory>
#include "Game.h"

int main() {
	std::shared_ptr<Game> game = GameFactroy::getGame();
	game->start();
	return 0; 
}
