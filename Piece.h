/************************************************************************
    > File Name: Piece.h
    > Author: huang
    > Mail: 13100937921@163.com 
    > Created Time: 2019年07月21日 星期日 08时52分42秒
************************************************************************/
#ifndef PIECE_H
#define PIECE_H
#include <memory>
#include "types.h"
#include "Position.h"
class Game;
class Piece;
class Player;


typedef std::shared_ptr<Piece>  PiecePtr;
typedef std::shared_ptr<Player> PlayerPtr;

class Piece {
public:
	Piece(PlayerPtr owner, ColorType color, RoleType role, StateType state = INIT, Position position = Position(-1, -1)) 
		: owner_(owner), color_(color), role_(role), state_(state), position_(position) {

	}
	Piece(const Piece&) = delete;
	Piece& operator=(const Piece&) = delete;

public:
	ColorType getColor() const { return color_; }
	RoleType getRole() const { return role_; }
	void setState(StateType state) { state_ = state; }
	StateType getState() const { return state_; }
	void setPosition(Position& pos) { position_ = pos; }
	Position getPosition() const { return position_; }
	PlayerPtr getOwner() const { return owner_; }

private:
	PlayerPtr		owner_;
	const ColorType color_;
	const RoleType  role_;
	StateType		state_;
	Position		position_;
}; 

//棋子工厂类，对外提供获取棋子的接口
class PieceFactory {
public:
//用于国际象棋，必须指定所有者，颜色，角色，状态和位置
	static PiecePtr getPiece(PlayerPtr& player, ColorType color, RoleType role, StateType state, Position& position) {
		return std::make_shared<Piece>(player, color, role, state, position);
	}
//用于围棋，必须指定所有者和颜色
	static PiecePtr getPiece(PlayerPtr& player, ColorType color) {
		return std::make_shared<Piece>(player, color, NOROLE, INIT);
	}
};

std::ostream& operator<<(std::ostream& os, PiecePtr& piece);

#endif
