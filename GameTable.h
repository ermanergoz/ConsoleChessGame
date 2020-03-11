#ifndef GAMETABLE_H
#define GAMETABLE_H
#pragma once
#include <cstdlib>

#include <vector>
#include <ostream>

#include "Tile.h"

class Piece;

class GameTable
{
private:
	std::size_t height;
	std::size_t width;

    std::vector<std::vector<Tile>> table;

public:
	struct Position
	{
		std::size_t row;	
		std::size_t col;

		Position(std::size_t _row = 0, std::size_t _col = 0) : row(_row), col(_col) {}
		bool operator==(const Position& other) const { return other.row == row && other.col == col; }
	};

    GameTable(std::size_t _height = 8, std::size_t _width = 8);
	~GameTable();

	std::size_t getHeight() const { return height; }
	std::size_t getWidth() const { return width; }

    void print(std::ostream & stream) const;

    Piece* getPieceAt(Position pos) { return table[pos.row][pos.col].getPiece(); } //nullptr if no piece there
    void setPieceTo(Position pos, Piece* piece) { table[pos.row][pos.col].setPiece(piece); }
};


#endif // GAMETABLE_H
