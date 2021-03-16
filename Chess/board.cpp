#include "board.hpp"

using namespace sf;

Board::Board() {
	for (int x = 0; x < 8; ++x) {
		for (int y = 0; y < 8; ++y) {
			board[x][y] = Piece();
		}
	}
	board[0][0] = Piece(KING, WHITE);
	
	board[0][0] = Piece(ROOK, WHITE);
	board[1][0] = Piece(KNIGHT, WHITE);
	board[2][0] = Piece(BISHOP, WHITE);
	board[3][0] = Piece(QUEEN, WHITE);
	board[4][0] = Piece(KING, WHITE);
	board[5][0] = Piece(BISHOP, WHITE);
	board[6][0] = Piece(KNIGHT, WHITE);
	board[7][0] = Piece(ROOK, WHITE);
	for (int i = 0; i < 8; ++i) { board[i][1] = Piece(PAWN, WHITE); }

	board[0][7] = Piece(ROOK, BLACK);
	board[1][7] = Piece(KNIGHT, BLACK);
	board[2][7] = Piece(BISHOP, BLACK);
	board[3][7] = Piece(QUEEN, BLACK);
	board[4][7] = Piece(KING, BLACK);
	board[5][7] = Piece(BISHOP, BLACK);
	board[6][7] = Piece(KNIGHT, BLACK);
	board[7][7] = Piece(ROOK, BLACK);
	for (int i = 0; i < 8; ++i) { board[i][6] = Piece(PAWN, BLACK); }
	
	
	// Extra
	board[3][2] = Piece(PAWN,WHITE);
	board[2][3] = Piece(PAWN, BLACK);
	board[4][3] = Piece(ROOK, BLACK);
	board[6][5] = Piece(ROOK, WHITE);

	//*/
}

std::vector<Vector2i> Board::getAllMoves(int x, int y) {
	std::vector<Vector2i> list;
	if (x == -1 || y == -1) { return list; }
	Piece current = board[x][y];
	int i, j;
	switch (current.team) {
	case NONE:
		break;
	case WHITE:
		switch (current.type) {
		case PAWN:
			if (y + 1 != 8 && board[x][y+1].type == EMPTY) { list.push_back(Vector2i(x,y + 1)); } // One ahead
			if (y == 1 && board[x][y + 2].type == EMPTY && board[x][y+1].type == EMPTY) { list.push_back(Vector2i(x, y + 2)); } // Two ahead first move
			if (x - 1 != -1 && y + 1 != 8 && board[x - 1][y + 1].team == BLACK) { list.push_back(Vector2i(x - 1, y + 1)); } // NW attack
			if (x + 1 != 8 && y + 1 != 8 && board[x + 1][y + 1].team == BLACK) { list.push_back(Vector2i(x + 1, y + 1)); } // NE attack
			break;
		case ROOK:
			// Negative X
			for (int i = x - 1; i != -1; --i) {
				if (board[i][y].type == EMPTY) { list.push_back(Vector2i(i, y)); }
				else if (board[i][y].team == BLACK) { list.push_back(Vector2i(i, y)); break; }
				else { break; }
			}
			// Positive X
			for (int i = x + 1; i != 8; ++i) {
				if (board[i][y].type == EMPTY) { list.push_back(Vector2i(i, y)); }
				else if (board[i][y].team == BLACK) { list.push_back(Vector2i(i, y)); break; }
				else { break; }
			}
			// Negative Y
			for (int i = y - 1; i != -1; --i) {
				if (board[x][i].type == EMPTY) { list.push_back(Vector2i(x, i)); }
				else if (board[x][i].team == BLACK) { list.push_back(Vector2i(x, i)); break; }
				else { break; }
			}
			// Positive X
			for (int i = y + 1; i != 8; ++i) {
				if (board[x][i].type == EMPTY) { list.push_back(Vector2i(x, i)); }
				else if (board[x][i].team == BLACK) { list.push_back(Vector2i(x, i)); break; }
				else { break; }
			}
			break;
		case KNIGHT:
			//ULL
			if (x - 2 >= 0 && y + 1 <= 7 && board[x - 2][y + 1].team != WHITE) { list.push_back(Vector2i(x - 2, y + 1)); }
			//UUL
			if (x - 1 >= 0 && y + 2 <= 7 && board[x - 1][y + 2].team != WHITE) { list.push_back(Vector2i(x - 1, y + 2)); }
			//UUR
			if (x + 1 <= 7 && y + 2 <= 7 && board[x + 1][y + 2].team != WHITE) { list.push_back(Vector2i(x + 1, y + 2)); }
			//URR
			if (x + 2 <= 7 && y + 1 <= 7 && board[x + 2][y + 1].team != WHITE) { list.push_back(Vector2i(x + 2, y + 1)); }
			//DRR
			if (x + 2 <= 7 && y - 1 >= 0 && board[x + 2][y - 1].team != WHITE) { list.push_back(Vector2i(x + 2, y - 1)); }
			//DDR
			if (x + 1 <= 7 && y - 2 >= 0 && board[x + 1][y - 2].team != WHITE) { list.push_back(Vector2i(x + 1, y - 2)); }
			//DDL
			if (x - 1 >= 0 && y - 2 >= 0 && board[x - 1][y - 2].team != WHITE) { list.push_back(Vector2i(x - 1, y - 2)); }
			//DLL
			if (x - 2 >= 0 && y - 1 >= 0 && board[x - 2][y - 1].team != WHITE) { list.push_back(Vector2i(x - 2, y - 1)); }
			break;
		case BISHOP:
			// NW
			i = x - 1, j = y + 1;
			while (i != -1 && j != 8) {
				if (board[i][j].team == NONE || board[i][j].team == BLACK) { list.push_back(Vector2i(i, j)); }
				if (board[i][j].team == WHITE || board[i][j].team == BLACK) { break; }
				--i; ++j;
			}
			// NE
			i = x + 1, j = y + 1;
			while (i != 8 && j != 8) {
				if (board[i][j].team == NONE || board[i][j].team == BLACK) { list.push_back(Vector2i(i, j)); }
				if (board[i][j].team == WHITE || board[i][j].team == BLACK) { break; }
				++i; ++j;
			}
			// SW
			i = x - 1, j = y - 1;
			while (i != -1 && j != -1) {
				if (board[i][j].team == NONE || board[i][j].team == BLACK) { list.push_back(Vector2i(i, j)); }
				if (board[i][j].team == WHITE || board[i][j].team == BLACK) { break; }
				--i; --j;
			}
			// SE
			i = x + 1, j = y - 1;
			while (i != 8 && j != -1) {
				if (board[i][j].team == NONE || board[i][j].team == BLACK) { list.push_back(Vector2i(i, j)); }
				if (board[i][j].team == WHITE || board[i][j].team == BLACK) { break; }
				++i; --j;
			}
			break;
		case QUEEN:
			// Negative X
			for (int i = x - 1; i != -1; --i) {
				if (board[i][y].type == EMPTY) { list.push_back(Vector2i(i, y)); }
				else if (board[i][y].team == BLACK) { list.push_back(Vector2i(i, y)); break; }
				else { break; }
			}
			// Positive X
			for (int i = x + 1; i != 8; ++i) {
				if (board[i][y].type == EMPTY) { list.push_back(Vector2i(i, y)); }
				else if (board[i][y].team == BLACK) { list.push_back(Vector2i(i, y)); break; }
				else { break; }
			}
			// Negative Y
			for (int i = y - 1; i != -1; --i) {
				if (board[x][i].type == EMPTY) { list.push_back(Vector2i(x, i)); }
				else if (board[x][i].team == BLACK) { list.push_back(Vector2i(x, i)); break; }
				else { break; }
			}
			// Positive X
			for (int i = y + 1; i != 8; ++i) {
				if (board[x][i].type == EMPTY) { list.push_back(Vector2i(x, i)); }
				else if (board[x][i].team == BLACK) { list.push_back(Vector2i(x, i)); break; }
				else { break; }
			}
			// NW
			i = x - 1, j = y + 1;
			while (i != -1 && j != 8) {
				if (board[i][j].team == NONE || board[i][j].team == BLACK) { list.push_back(Vector2i(i, j)); }
				if (board[i][j].team == WHITE || board[i][j].team == BLACK) { break; }
				--i; ++j;
			}
			// NE
			i = x + 1, j = y + 1;
			while (i != 8 && j != 8) {
				if (board[i][j].team == NONE || board[i][j].team == BLACK) { list.push_back(Vector2i(i, j)); }
				if (board[i][j].team == WHITE || board[i][j].team == BLACK) { break; }
				++i; ++j;
			}
			// SW
			i = x - 1, j = y - 1;
			while (i != -1 && j != -1) {
				if (board[i][j].team == NONE || board[i][j].team == BLACK) { list.push_back(Vector2i(i, j)); }
				if (board[i][j].team == WHITE || board[i][j].team == BLACK) { break; }
				--i; --j;
			}
			// SE
			i = x + 1, j = y - 1;
			while (i != 8 && j != -1) {
				if (board[i][j].team == NONE || board[i][j].team == BLACK) { list.push_back(Vector2i(i, j)); }
				if (board[i][j].team == WHITE || board[i][j].team == BLACK) { break; }
				++i; --j;
			}
			break;
		case KING:
			// NW
			if (x - 1 != -1 && y + 1 != 8 && board[x - 1][y + 1].team != WHITE) { list.push_back(Vector2i(x - 1, y + 1)); }
			// N
			if (y + 1 != 8 && board[x][y + 1].team != WHITE) { list.push_back(Vector2i(x, y + 1)); }
			// NE
			if (x + 1 != 8 && y + 1 != 8 && board[x + 1][y + 1].team != WHITE) { list.push_back(Vector2i(x + 1, y + 1)); }
			// E
			if (x + 1 != 8 && board[x + 1][y].team != WHITE) { list.push_back(Vector2i(x + 1, y)); }
			// SE
			if (x + 1 != 8 && y - 1 != -1 && board[x + 1][y - 1].team != WHITE) { list.push_back(Vector2i(x + 1, y - 1)); }
			// S
			if (y - 1 != -1 && board[x][y - 1].team != WHITE) { list.push_back(Vector2i(x, y - 1)); }
			// SW
			if (x - 1 != -1 && y - 1 != -1 && board[x - 1][y - 1].team != WHITE) { list.push_back(Vector2i(x - 1, y - 1)); }
			// W
			if (x - 1 != -1 && board[x - 1][y].team != WHITE) { list.push_back(Vector2i(x - 1, y)); }
			break;
		}
		break;
	case BLACK:
		switch (current.type) {
		case PAWN:
			if (y - 1 != -1 && board[x][y - 1].type == EMPTY) { list.push_back(Vector2i(x, y - 1)); }
			if (y == 6 && board[x][y - 2].type == EMPTY && board[x][y - 1].type == EMPTY) { list.push_back(Vector2i(x, y - 2)); }
			if (x - 1 != -1 && y - 1 != -1 && board[x - 1][y - 1].team == WHITE) { list.push_back(Vector2i(x - 1, y - 1)); }
			if (x + 1 != -1 && y - 1 != -1 && board[x + 1][y - 1].team == WHITE) { list.push_back(Vector2i(x + 1, y - 1)); }
			break;
		case ROOK:
			// Negative X
			for (int i = x - 1; i != -1; --i) {
				if (board[i][y].type == EMPTY) { list.push_back(Vector2i(i, y)); }
				else if (board[i][y].team == WHITE) { list.push_back(Vector2i(i, y)); break; }
				else { break; }
			}
			// Positive X
			for (int i = x + 1; i != 8; ++i) {
				if (board[i][y].type == EMPTY) { list.push_back(Vector2i(i, y)); }
				else if (board[i][y].team == WHITE) { list.push_back(Vector2i(i, y)); break; }
				else { break; }
			}
			// Negative Y
			for (int i = y - 1; i != -1; --i) {
				if (board[x][i].type == EMPTY) { list.push_back(Vector2i(x, i)); }
				else if (board[x][i].team == WHITE) { list.push_back(Vector2i(x, i)); break; }
				else { break; }
			}
			// Positive X
			for (int i = y + 1; i != 8; ++i) {
				if (board[x][i].type == EMPTY) { list.push_back(Vector2i(x, i)); }
				else if (board[x][i].team == WHITE) { list.push_back(Vector2i(x, i)); break; }
				else { break; }
			}
			break;
		case KNIGHT:
			//ULL
			if (x - 2 >= 0 && y + 1 <= 7 && board[x - 2][y + 1].team != BLACK) { list.push_back(Vector2i(x - 2, y + 1)); }
			//UUL
			if (x - 1 >= 0 && y + 2 <= 7 && board[x - 1][y + 2].team != BLACK) { list.push_back(Vector2i(x - 1, y + 2)); }
			//UUR
			if (x + 1 <= 7 && y + 2 <= 7 && board[x + 1][y + 2].team != BLACK) { list.push_back(Vector2i(x + 1, y + 2)); }
			//URR
			if (x + 2 <= 7 && y + 1 <= 7 && board[x + 2][y + 1].team != BLACK) { list.push_back(Vector2i(x + 2, y + 1)); }
			//DRR
			if (x + 2 <= 7 && y - 1 >= 0 && board[x + 2][y - 1].team != BLACK) { list.push_back(Vector2i(x + 2, y - 1)); }
			//DDR
			if (x + 1 <= 7 && y - 2 >= 0 && board[x + 1][y - 2].team != BLACK) { list.push_back(Vector2i(x + 1, y - 2)); }
			//DDL
			if (x - 1 >= 0 && y - 2 >= 0 && board[x - 1][y - 2].team != BLACK) { list.push_back(Vector2i(x - 1, y - 2)); }
			//DLL
			if (x - 2 >= 0 && y - 1 >= 0 && board[x - 2][y - 1].team != BLACK) { list.push_back(Vector2i(x - 2, y - 1)); }
			break;
		case BISHOP:
			// NW
			i = x - 1, j = y + 1;
			while (i != -1 && j != 8) {
				if (board[i][j].team == NONE || board[i][j].team == WHITE) { list.push_back(Vector2i(i, j)); }
				if (board[i][j].team == WHITE || board[i][j].team == BLACK) { break; }
				--i; ++j;
			}
			// NE
			i = x + 1, j = y + 1;
			while (i != 8 && j != 8) {
				if (board[i][j].team == NONE || board[i][j].team == WHITE) { list.push_back(Vector2i(i, j)); }
				if (board[i][j].team == WHITE || board[i][j].team == BLACK) { break; }
				++i; ++j;
			}
			// SW
			i = x - 1, j = y - 1;
			while (i != -1 && j != -1) {
				if (board[i][j].team == NONE || board[i][j].team == WHITE) { list.push_back(Vector2i(i, j)); }
				if (board[i][j].team == WHITE || board[i][j].team == BLACK) { break; }
				--i; --j;
			}
			// SE
			i = x + 1, j = y - 1;
			while (i != 8 && j != -1) {
				if (board[i][j].team == NONE || board[i][j].team == WHITE) { list.push_back(Vector2i(i, j)); }
				if (board[i][j].team == WHITE || board[i][j].team == BLACK) { break; }
				++i; --j;
			}
			break;
		case QUEEN:
			// Negative X
			for (int i = x - 1; i != -1; --i) {
				if (board[i][y].type == EMPTY) { list.push_back(Vector2i(i, y)); }
				else if (board[i][y].team == WHITE) { list.push_back(Vector2i(i, y)); break; }
				else { break; }
			}
			// Positive X
			for (int i = x + 1; i != 8; ++i) {
				if (board[i][y].type == EMPTY) { list.push_back(Vector2i(i, y)); }
				else if (board[i][y].team == WHITE) { list.push_back(Vector2i(i, y)); break; }
				else { break; }
			}
			// Negative Y
			for (int i = y - 1; i != -1; --i) {
				if (board[x][i].type == EMPTY) { list.push_back(Vector2i(x, i)); }
				else if (board[x][i].team == WHITE) { list.push_back(Vector2i(x, i)); break; }
				else { break; }
			}
			// Positive X
			for (int i = y + 1; i != 8; ++i) {
				if (board[x][i].type == EMPTY) { list.push_back(Vector2i(x, i)); }
				else if (board[x][i].team == WHITE) { list.push_back(Vector2i(x, i)); break; }
				else { break; }
			}
			// NW
			i = x - 1, j = y + 1;
			while (i != -1 && j != 8) {
				if (board[i][j].team == NONE || board[i][j].team == WHITE) { list.push_back(Vector2i(i, j)); }
				if (board[i][j].team == WHITE || board[i][j].team == BLACK) { break; }
				--i; ++j;
			}
			// NE
			i = x + 1, j = y + 1;
			while (i != 8 && j != 8) {
				if (board[i][j].team == NONE || board[i][j].team == WHITE) { list.push_back(Vector2i(i, j)); }
				if (board[i][j].team == WHITE || board[i][j].team == BLACK) { break; }
				++i; ++j;
			}
			// SW
			i = x - 1, j = y - 1;
			while (i != -1 && j != -1) {
				if (board[i][j].team == NONE || board[i][j].team == WHITE) { list.push_back(Vector2i(i, j)); }
				if (board[i][j].team == WHITE || board[i][j].team == BLACK) { break; }
				--i; --j;
			}
			// SE
			i = x + 1, j = y - 1;
			while (i != 8 && j != -1) {
				if (board[i][j].team == NONE || board[i][j].team == WHITE) { list.push_back(Vector2i(i, j)); }
				if (board[i][j].team == WHITE || board[i][j].team == BLACK) { break; }
				++i; --j;
			}
			break;
		case KING:
			// NW
			if (x - 1 != -1 && y + 1 != 8 && board[x - 1][y + 1].team != BLACK) { list.push_back(Vector2i(x - 1, y + 1)); }
			// N
			if (y + 1 != 8 && board[x][y + 1].team != BLACK) { list.push_back(Vector2i(x, y + 1)); }
			// NE
			if (x + 1 != 8 && y + 1 != 8 && board[x + 1][y + 1].team != BLACK) { list.push_back(Vector2i(x + 1, y + 1)); }
			// E
			if (x + 1 != 8 && board[x + 1][y].team != BLACK) { list.push_back(Vector2i(x + 1, y)); }
			// SE
			if (x + 1 != 8 && y - 1 != -1 && board[x + 1][y - 1].team != BLACK) { list.push_back(Vector2i(x + 1, y - 1)); }
			// S
			if (y - 1 != -1 && board[x][y - 1].team != BLACK) { list.push_back(Vector2i(x, y - 1)); }
			// SW
			if (x - 1 != -1 && y - 1 != -1 && board[x - 1][y - 1].team != BLACK) { list.push_back(Vector2i(x - 1, y - 1)); }
			// W
			if (x - 1 != -1 && board[x - 1][y].team != BLACK) { list.push_back(Vector2i(x - 1, y)); }
			break;
		}
	}

	return list;
}
