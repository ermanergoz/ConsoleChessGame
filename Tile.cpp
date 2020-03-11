#include "Tile.h"
#include "Piece.h"
#include <windows.h>

Tile::Tile(std::size_t _row, std::size_t _col, Piece* _piece) : piece(_piece), row(_row), col(_col)
{
    if((row + col) % 2 == 0)
    {
        color = Color::WHITE;
    }
    else
    {
        color = Color::BLACK;
    }
}

void Tile::setPiece(Piece *_piece)  
{
     piece = _piece;
     if(_piece) 
     {
         piece->step(GameTable::Position(row, col));    
     }
}

void Tile::print(std::ostream &stream) const
{
    if(color == Color::BLACK)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    }

    stream << "|";
    if(piece)
    {
        piece->print(stream);
    }
    else
    {
        stream << " ";  
    }
    stream << "|";

    if(color == Color::BLACK)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
}
