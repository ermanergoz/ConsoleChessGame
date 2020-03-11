#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include "GameModel.h"

class GameWindow
{
private:
    GameModel* model;
    std::string errorMessage;
    std::string instruction;
    std::string userInput;

    void clearWindow();
    void printTable(std::ostream& stream);
    void printError(std::ostream& stream);
    void printInstruction(std::ostream& stream);
    void printGameOver(std::ostream& stream);
    void selectPiece(std::ostream &stream);
    void stepPiece(std::ostream &stream);

public:
    GameWindow();
    ~GameWindow();

    void print(std::ostream& stream);
};

#endif

