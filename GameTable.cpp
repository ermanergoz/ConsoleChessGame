#include "GameTable.h"


GameTable::GameTable(std::size_t _height, std::size_t _width) : height(_height), width(_width)
{
    for(std::size_t row = 0; row < height; ++row)
    {
        std::vector<Tile> newRow;   
        table.push_back(newRow);

        for(std::size_t col = 0; col < width; ++col)
        {
            table[row].push_back(Tile(row, col));   
        }
    }
}

GameTable::~GameTable()
{
}

void GameTable::print(std::ostream &stream) const
{
    std::size_t rowNum = 0;
    for(const auto& row : table)
    {
        for(const auto& tile : row)
        {
            tile.print(stream); 

        }
        stream << " " << static_cast<char>('A' + rowNum) << "\n";
        ++rowNum;
    }
}
