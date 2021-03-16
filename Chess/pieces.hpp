#ifndef PIECES_HPP_
#define PIECES_HPP_

#include <iostream>;

const char* const PIECE_NAME_LIST[] = { 
	"EMPTY", "Pawn", "Rook", "Knight", "Bishop", "Queen", "King",
	"Pawn With Gun", "Double Bishop", "Checker", "King Checker", "Prince", "Princess", "Assassin",
};

const char* const TEAM_NAME_LIST[] = {
	"None", "White", "Black"
};

enum Piece_Type {
	//Normal Pieces
	EMPTY = 0, PAWN = 1, ROOK = 2, KNIGHT = 3, BISHOP = 4, QUEEN = 5, KING = 6,

	//Advanced Pieces
	PAWN_WITH_GUN = 7, DOUBLE_BISHOP = 8, CHECKER = 9, KING_CHECKER = 10, PRINCE = 11, PRINCESS = 12, ASSASSIN = 13,
};

enum Team {
	NONE = 0, WHITE = 1, BLACK = 2,
};


class Piece {
public:
	Piece();
	Piece(Piece_Type, Team);
	void print();
	Piece_Type type;
	Team team;
};

#endif