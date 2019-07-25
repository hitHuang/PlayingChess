/************************************************************************
    > File Name: types.h
    > Author: huang
    > Mail: moon7921@163.com 
    > Created Time: 2019年07月21日 星期日 08时37分35秒
************************************************************************/
#ifndef TYPES_H
#define TYPES_H
typedef enum {
	CHESS, GO
} GameType;

typedef enum {
	READY, RUNNING, OVER
} GameState;

typedef enum {
	PLAYER1, PLAYER2
} PlayerType;

typedef enum {
	WHITE, BLACK
} ColorType;

typedef enum {
	INIT, ONBOARD, DEAD
} PieceState;

typedef enum {
	NOROLE, KING, QUEEN, ROOK, KNIGHT, BISHOP, PAWN
} RoleType;

typedef enum {
	END, YIELD, PLACE, MOVE, WIPE, EAT, QUERY, STAT, INVALID
} OpType;

#endif
