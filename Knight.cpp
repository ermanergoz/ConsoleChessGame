#include "Knight.h"
#include <windows.h>

Knight::Knight(GameTable& _table, const GameTable::Position& _position, Player _player) : Piece(_table, _position, _player)
{
}


Knight::~Knight()
{
}

void Knight::print(std::ostream & stream) const //this should be brown if player is black and white otherwise
{
    WORD originalColor;
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info); //for the colors
    originalColor = info.wAttributes;

    if(player == Piece::Player::BLACK)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }

    stream << "H";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), originalColor);
}

void Knight::refreshAvailableSteps()
{
    std::vector<GameTable::Position> newAvailableSteps;

    if(position.row > 0 && position.col > 1) //up & left down
    {
        GameTable::Position toCheck(position.row - 1, position.col - 2 );
        pushIfCanStepThere(toCheck, newAvailableSteps);
    }

    if(position.row > 1 && position.col > 0) //up & left up
    {
        GameTable::Position toCheck(position.row - 2, position.col - 1 );
        pushIfCanStepThere(toCheck, newAvailableSteps);
    }

    if(position.row > 0 && position.col + 2 < table.getWidth()) //up & right down
    {
        GameTable::Position toCheck(position.row - 1, position.col + 2);
        pushIfCanStepThere(toCheck, newAvailableSteps);
    }

    if(position.row > 1 && position.col + 1 < table.getWidth()) //up & right up
    {
        GameTable::Position toCheck(position.row - 2, position.col + 1);
        pushIfCanStepThere(toCheck, newAvailableSteps);
    }

    if(position.row + 2 < table.getHeight() && position.col > 0) //down & left down
    {
        GameTable::Position toCheck(position.row + 2, position.col - 1);
        pushIfCanStepThere(toCheck, newAvailableSteps);
    }

    if(position.row + 1 < table.getHeight() && position.col > 1) //down & left up
    {
        GameTable::Position toCheck(position.row + 1, position.col - 2);
        pushIfCanStepThere(toCheck, newAvailableSteps);
    }

    if(position.row + 2 < table.getHeight() && position.col + 1 < table.getWidth()) //down & right down
    {
        GameTable::Position toCheck(position.row + 2, position.col + 1);
        pushIfCanStepThere(toCheck, newAvailableSteps);
    }

    if(position.row + 1 < table.getHeight() && position.col + 2 < table.getWidth()) //down & right up
    {
        GameTable::Position toCheck(position.row + 1, position.col + 2);
        pushIfCanStepThere(toCheck, newAvailableSteps);
    }

    availablePositions = newAvailableSteps;
}

void Knight::pushIfCanStepThere(const GameTable::Position &toCheck, std::vector<GameTable::Position> &toPushTo)
{
    const Piece* pieceAtThere = table.getPieceAt(toCheck);      

    if(!pieceAtThere || (pieceAtThere->getPlayer() != player))
    {
        toPushTo.push_back(toCheck);
    }
}
