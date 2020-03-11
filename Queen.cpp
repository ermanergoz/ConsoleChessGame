#include "Queen.h"
#include <windows.h>

Queen::Queen(GameTable &_table, const GameTable::Position &_position, Player _player) : Piece(_table, _position, _player)
{
}

Queen::~Queen()
{

}

void Queen::print(std::ostream &stream) const
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

    stream << "Q";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), originalColor);
}

void Queen::refreshAvailableSteps()
{	std::vector<GameTable::Position> newAvailableSteps;

    if (0 < position.row) //up
    {
        for (int i = position.row - 1; i >= 0; --i)
        {
            GameTable::Position current(i, position.col);
            const Piece* pieceAtThere = table.getPieceAt(current);
            if(!pieceAtThere) // is nothing
            {
                newAvailableSteps.push_back(current);
            }
            else if (pieceAtThere->getPlayer() == player) // is teammate || king?
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

    if (position.row + 1 < table.getHeight()) //down, +1 because of indexing diferrence
    {
        for (std::size_t i = position.row + 1; i < table.getHeight(); ++i)
        {
            GameTable::Position current(i, position.col);
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

    if (0 < position.row)
    {
        if(0 < position.col)
        {
            for (int row = position.row - 1, col = position.col - 1; row >= 0 && col >= 0; --row, --col) //up & left
            {
                GameTable::Position current(row, col);
                const Piece* pieceAtThere = table.getPieceAt(current);
                if(!pieceAtThere) // is nothing
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

        if(position.col + 1 < table.getWidth())
        {
            int row;
            std::size_t col;
            for (row = position.row - 1, col = position.col + 1; row >= 0 && col < table.getWidth(); --row, ++col) // up & right
            {
                GameTable::Position current(row, col);
                const Piece* pieceAtThere = table.getPieceAt(current);
                if(!pieceAtThere) // is nothing
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
    }

    if (position.row + 1 < table.getHeight())
    {
        if(0 < position.col)
        {
            std::size_t row;
            int col;
            for (row = position.row + 1, col = position.col - 1; row < table.getHeight() && col >= 0; ++row, --col) //down & left
            {
                GameTable::Position current(row, col);
                const Piece* pieceAtThere = table.getPieceAt(current);
                if(!pieceAtThere) // is nothing
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

        if(position.col + 1 < table.getWidth())
        {
            for (std::size_t row = position.row + 1, col = position.col + 1; row < table.getHeight() && col < table.getWidth(); ++row, ++col) // down & right
            {
                GameTable::Position current(row, col);
                const Piece* pieceAtThere = table.getPieceAt(current);
                if(!pieceAtThere) // is nothing
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
    }

    availablePositions = newAvailableSteps;
}
