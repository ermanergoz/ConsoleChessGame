#include "Rook.h"
#include <windows.h>

Rook::Rook(GameTable& _table, const GameTable::Position& _position, Player _player) : Piece(_table, _position, _player)
{
}


Rook::~Rook()
{
}

void Rook::print(std::ostream & stream) const //this should be brown if player is black and white otherwise
{
    WORD originalColor;
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    originalColor = info.wAttributes;

    if(player == Piece::Player::BLACK)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }

    stream << "R";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), originalColor); // so color wont stay white or brown forever
}

/* protected and pure virt */ void Rook::refreshAvailableSteps()
{
    std::vector<GameTable::Position> newAvailableSteps;

	if (0 < position.row) //up
	{
        for (int i = position.row - 1; i >= 0; --i)
		{
			GameTable::Position current(i, position.col);
			const Piece* pieceAtThere = table.getPieceAt(current);

			if(!pieceAtThere) // is nothing
			{
				newAvailableSteps.push_back(current); //we go until the end or until it meets with a piece
			}
            else if (pieceAtThere->getPlayer() == player) // is teammate || king?
			{
				break;  //i fit is a friend
			}
			else
			{
				newAvailableSteps.push_back(current);   //we step on enemies head
				break;  //we break because it is the last position we can step
			}
		}
	}

    if (position.row + 1 < table.getHeight()) //down, +1 because of indexing diferrence
	{
		for (std::size_t i = position.row + 1; i < table.getHeight(); ++i)
		{
			GameTable::Position current(i, position.col);
			const Piece* pieceAtThere = table.getPieceAt(current);
			if (!pieceAtThere) // is nothing
			{
				newAvailableSteps.push_back(current); //to add element at the end of the vector
			}
            else if (pieceAtThere->getPlayer() == player)
			{
				break;
			}
			else
			{
				newAvailableSteps.push_back(current);   //++++what is this for?
				break;
			}
		}
	}

	if (0 < position.col) //left
	{
        for (int i = position.col - 1; i >= 0; --i)
		{
			GameTable::Position current(position.row, i);
			const Piece* pieceAtThere = table.getPieceAt(current);
			if (!pieceAtThere) // is nothing
			{
				newAvailableSteps.push_back(current);
			}
            else if (pieceAtThere->getPlayer() == player)
			{
				break;
			}
			else
			{
				newAvailableSteps.push_back(current);
				break;
			}
		}
	}

    if (position.col + 1 < table.getWidth()) //right, +1 because of indexing diferrence
	{
        for (std::size_t i = position.col + 1; i < table.getWidth(); ++i)
		{
			GameTable::Position current(position.row, i);
			const Piece* pieceAtThere = table.getPieceAt(current);
			if (!pieceAtThere) // is nothing
			{
				newAvailableSteps.push_back(current);
			}
            else if (pieceAtThere->getPlayer() == player)
			{
				break;
			}
			else
			{
				newAvailableSteps.push_back(current);
				break;
			}
		}
    }

    availablePositions = newAvailableSteps; //new available steps is not necessary
}

