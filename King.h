#ifndef KING_H
#define KING_H
#pragma once
#include "Piece.h"

class King : public Piece
{
public:
    King(GameTable& _table, const GameTable::Position& _position, Player _player);
    ~King();

    void print(std::ostream& stream) const;

protected:
    void refreshAvailableSteps();

private:
    void pushIfCanStepThere(const GameTable::Position& toCheck, std::vector<GameTable::Position>& toPushTo);
};



#endif // KING_H
