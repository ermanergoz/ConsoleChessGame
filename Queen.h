#ifndef QUEEN_H
#define QUEEN_H
#pragma once
#include "Piece.h"

class Queen : public Piece
{
public:
    Queen(GameTable& _table, const GameTable::Position& _position, Player _player);
    ~Queen();

    void print(std::ostream& stream) const;

protected:
    void refreshAvailableSteps();
};



#endif // QUEEN_H
