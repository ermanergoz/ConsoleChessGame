#include "Piece.h"
#include <stdexcept>


Piece::Piece(GameTable& _table, const GameTable::Position& _position, Player _player) : table(_table), position(_position), player(_player)
{
}


Piece::~Piece()
{
}

std::vector<GameTable::Position> Piece::availableSteps()
{
    refreshAvailableSteps();    
                                

	return availablePositions;
}

bool Piece::canMove()
{

	if (availableSteps().size() != 0)	
	{
		return true;
	}
	return false;
}

 bool Piece::canMoveTo(const GameTable::Position& toStepTo)
{
	for (const auto& position : availableSteps())
	{                                           
		if (position == toStepTo)
		{
			return true;
		}
	}

	return false;
}

void Piece::step(const GameTable::Position & toStepTo)  
{
    position = toStepTo;
}
