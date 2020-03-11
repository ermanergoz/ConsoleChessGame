#ifndef KNIGHT_H
#define KNIGHT_H
#pragma once
#include "Piece.h"


class Knight : public Piece
{
public:
    Knight(GameTable& _table, const GameTable::Position& _position, Player _player);
	~Knight();

    void print(std::ostream& stream) const;

protected:
	void refreshAvailableSteps();

private:
    void pushIfCanStepThere(const GameTable::Position &toCheck, std::vector<GameTable::Position> &toPushTo);
};



#endif // KNIGHT_H
