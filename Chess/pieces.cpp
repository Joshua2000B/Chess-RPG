#include "pieces.hpp"

Piece::Piece() {
	type = EMPTY;
	team = NONE;
}

Piece::Piece(Piece_Type pt, Team tm) {
	type = pt;
	team = tm;
}

void Piece::print() {
	std::cout << TEAM_NAME_LIST[team] << ' ' << PIECE_NAME_LIST[type] << std::endl;
}