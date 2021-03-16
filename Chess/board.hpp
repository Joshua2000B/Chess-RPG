#include "pieces.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

#ifndef BOARD_HPP_
#define BOARD_HPP_

class Board {
public:
	Board();
	Piece board[8][8];
	std::vector<sf::Vector2i> getAllMoves(int, int);
};

#endif