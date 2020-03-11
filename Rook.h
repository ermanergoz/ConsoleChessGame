#ifndef ROOK_H
#define ROOK_H
#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
    Rook(GameTable& _table, const GameTable::Position& _position, Player _player);
	~Rook();

    void print(std::ostream& stream) const;

protected:
	void refreshAvailableSteps();
};


#endif // ROOK_H
