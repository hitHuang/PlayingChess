/************************************************************************
    > File Name: Operation.cpp
    > Author: huang
    > Mail: 13100937921@163.com 
    > Created Time: 2019年07月22日 星期一 16时13分19秒
************************************************************************/

#include "Operation.h"
#include <unordered_map>
#include <string>

using std::cin;

std::unordered_map<std::string, OpType> str2op = {
	{"end", END}, {"yield",YIELD}, {"place", PLACE}, {"move",MOVE},
	{"wipe", WIPE}, {"eat", EAT}, {"query", QUERY}, {"stat", STAT},
};

std::unordered_map<OpType, std::string> op2str = {
	{END, "end"}, {YIELD, "yield"}, {PLACE, "place"}, {MOVE, "move"},
	{WIPE, "wipe"}, {EAT, "eat"}, {QUERY, "query"}, {STAT, "stat"}, {INVALID, "invalid"}
};

void Operation::readCommand() {
	std::string command;
	cin >> command;
	if (str2op.find(command) == str2op.end()) {
		setType(INVALID);
		return ;
	}
	setType(str2op[command]);
	OpType op = getType();
	int x1, x2, y1, y2;
	if (op == END || op == YIELD || op == STAT) return ;
	if (op == PLACE || op == WIPE || op == QUERY) {
		cin >> x1 >> y1;
		Position position(x1, y1);
		setPosition1(position);
		return ;
	}
	if (op == MOVE || op == EAT) {
		cin >> x1 >> y1 >> x2 >> y2;
		Position position1(x1, y1);
		Position position2(x2, y2);
		setPosition1(position1);
		setPosition2(position2);
	}
}

std::string Operation::toStr() {
	std::string res;
	OpType op = getType();
	res += op2str[op];
	if (op == PLACE || op == WIPE || op == QUERY) {
		res += " pos1(";
		res += getPosition1().toStr();
		res += ") ";
	}
	else if (op == MOVE || op == EAT) {
		res += " pos1(";
		res += getPosition1().toStr();
		res += ") ";
		res += " pos2(";
		res += getPosition2().toStr();
		res += ") ";
	}
	return res;
}

std::ostream& operator<<(std::ostream& os, Operation& op) {
	os << "op: " << op2str[op.getType()] << "  ";
	os << "pos1: " << op.getPosition1() << "  ";
	os << "pos2: " << op.getPosition2();
}