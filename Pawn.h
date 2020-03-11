#ifndef PAWN_H
#define PAWN_H
#pragma once
#include "Piece.h"


class Pawn : public Piece
{
public:
    Pawn(GameTable& _table, const GameTable::Position& _position, Player _player);
	~Pawn();

    void print(std::ostream& stream) const;

protected:
	void refreshAvailableSteps();
};

#endif // PAWN_H
