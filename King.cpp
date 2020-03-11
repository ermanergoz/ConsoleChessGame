#include "King.h"
#include <windows.h>

King::King(GameTable &_table, const GameTable::Position &_position, Player _player) : Piece(_table, _position, _player)
{
}

King::~King()
{

}

void King::print(std::ostream &stream) const
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

    stream << "K";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), originalColor);
}

void King::refreshAvailableSteps()
{
    std::vector<GameTable::Position> newAvailableSteps;

    if(position.row > 0 && position.col > 0) //up & left
    {
        GameTable::Position toCheck(position.row - 1, position.col - 1);
        pushIfCanStepThere(toCheck, newAvailableSteps);
    }

    if(position.row > 0) //up & center
    {
        GameTable::Position toCheck(position.row - 1, position.col);
        pushIfCanStepThere(toCheck, newAvailableSteps);
    }

    if(position.row > 0 && position.col + 1 < table.getWidth()) //up & right
    {
        GameTable::Position toCheck(position.row - 1, position.col + 1);
        pushIfCanStepThere(toCheck, newAvailableSteps);
    }

    if(position.col > 0) //center & left
    {
        GameTable::Position toCheck(position.row , position.col - 1);
        pushIfCanStepThere(toCheck, newAvailableSteps);
    }

    if(position.col + 1 < table.getWidth()) //center & right
    {
        GameTable::Position toCheck(position.row, position.col + 1);
        pushIfCanStepThere(toCheck, newAvailableSteps);
    }

    if(position.row + 1 < table.getHeight() && position.col > 0) //down & left
    {
        GameTable::Position toCheck(position.row + 1, position.col - 1);
        pushIfCanStepThere(toCheck, newAvailableSteps);
    }

    if(position.row + 1 < table.getHeight())
    {
        GameTable::Position toCheck(position.row + 1, position.col); //down & center
        pushIfCanStepThere(toCheck, newAvailableSteps);
    }

    if(position.row + 1 < table.getHeight() && position.col + 1 < table.getWidth()) //down & right
    {
        GameTable::Position toCheck(position.row + 1, position.col + 1);
        pushIfCanStepThere(toCheck, newAvailableSteps);
    }

    availablePositions = newAvailableSteps;
}

void King::pushIfCanStepThere(const GameTable::Position &toCheck, std::vector<GameTable::Position> &toPushTo)
{
    const Piece* pieceAtThere = table.getPieceAt(toCheck);      

    if(!pieceAtThere || pieceAtThere->getPlayer() != player)
    {
        toPushTo.push_back(toCheck);
    }
}
