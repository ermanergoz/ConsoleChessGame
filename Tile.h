#ifndef TILE_H
#define TILE_H


#include <cstdlib>
#include <ostream>

class Piece;

class Tile
{
private:
    enum class Color { BLACK, WHITE };

    Color color;
    Piece* piece;   
    std::size_t row;
    std::size_t col;

public:
    Tile(std::size_t _row, std::size_t _col, Piece* _piece = nullptr);
    Piece* getPiece() { return piece; }
    const Piece* getPiece() const { return piece; }
    void setPiece(Piece* _piece);

    void print(std::ostream & stream) const;
};



#endif // TILE_H
