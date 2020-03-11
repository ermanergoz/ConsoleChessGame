#ifndef PIECE_H
#define PIECE_H
#pragma once
#include<vector>
#include<ostream>
#include"GameTable.h"

class Piece
{
public:
	enum class Player 
	{
		BLACK, WHITE
	};


    std::vector<GameTable::Position> availableSteps();
    bool canMove(); //asking whther can move at all
    bool canMoveTo(const GameTable::Position& toStepTo); 
	void step(const GameTable::Position& toStepTo);	
    virtual void print(std::ostream& stream) const = 0;
    Player getPlayer() const { return player; }
    GameTable::Position getPosition() const { return position; }

    Piece(GameTable& _table, const GameTable::Position& _position, Player _player);
	virtual ~Piece();

protected:
    GameTable &table;
	GameTable::Position position;   
	Player player; 
	std::vector<GameTable::Position> availablePositions;
//it knows which steps are available, i am a pretty rook
	virtual void refreshAvailableSteps() = 0;
};


#endif // PIECE_H
