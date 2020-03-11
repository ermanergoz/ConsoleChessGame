#include "Pawn.h"
#include <windows.h>

Pawn::Pawn(GameTable& _table, const GameTable::Position& _position, Player _player) : Piece(_table, _position, _player)
{
}


Pawn::~Pawn()
{
}

void Pawn::print(std::ostream & stream) const //this should be brown if player is black and white otherwise
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

    stream << "P";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), originalColor);
}

/* protected */ void Pawn::refreshAvailableSteps()
{
    std::vector<GameTable::Position> newAvailableSteps;

    if(player == Piece::Player::WHITE)
    {
        if (0 < position.row) //up
        {
            GameTable::Position inFront(position.row - 1, position.col);

            const Piece* pieceAtThere = table.getPieceAt(inFront);
            if(!pieceAtThere)
            {
                newAvailableSteps.push_back(inFront);
            }

            if(position.col + 1 < table.getWidth()) //up & right
            {
                GameTable::Position diagonalUpRight(position.row - 1, position.col + 1);

                pieceAtThere = table.getPieceAt(diagonalUpRight);
                if(pieceAtThere && pieceAtThere->getPlayer() != player)
                {
                    newAvailableSteps.push_back(diagonalUpRight);
                }
            }

            if(position.col > 0) //up & left
            {
                GameTable::Position diagonalUpLeft(position.row - 1, position.col - 1);

                pieceAtThere = table.getPieceAt(diagonalUpLeft);
                if(pieceAtThere && pieceAtThere->getPlayer() != player)
                {
                    newAvailableSteps.push_back(diagonalUpLeft);
                }
            }
        }
    }
    else
    {
        if (table.getHeight() - 1 > position.row) //down
        {
            GameTable::Position inFront(position.row + 1, position.col);

            const Piece* pieceAtThere = table.getPieceAt(inFront);
            if(!pieceAtThere)
            {
                newAvailableSteps.push_back(inFront);
            }

            if(position.col + 1 < table.getWidth()) //down & right
            {
                GameTable::Position diagonalDownRight(position.row + 1, position.col + 1);

                pieceAtThere = table.getPieceAt(diagonalDownRight);
                if(pieceAtThere && pieceAtThere->getPlayer() != player)
                {
                    newAvailableSteps.push_back(diagonalDownRight);
                }
            }

            if(position.col > 0) //down & left
            {
                GameTable::Position diagonalDownLeft(position.row + 1, position.col - 1);

                pieceAtThere = table.getPieceAt(diagonalDownLeft);
                if(pieceAtThere && pieceAtThere->getPlayer() != player)
                {
                    newAvailableSteps.push_back(diagonalDownLeft);
                }
            }
        }
    }

    availablePositions = newAvailableSteps;
}
