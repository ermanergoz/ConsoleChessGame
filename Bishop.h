#ifndef BISHOP_H
#define BISHOP_H
#pragma once
#include "Piece.h"


class Bishop : public Piece
{
public:
    Bishop(GameTable& _table, const GameTable::Position& _position, Player _player);
	~Bishop();

    void print(std::ostream& stream) const;

protected:
	void refreshAvailableSteps();
};



#endif // BISHOP_H
