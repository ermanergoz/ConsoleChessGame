#include "GameWindow.h"
#include <iostream>
#include <fstream>
using namespace std;

GameWindow::GameWindow() : model(new GameModel), errorMessage(""), instruction("Select a piece"), userInput("")
{
    model->startNewGame();
    print(std::cout);
    selectPiece(std::cout);
}

GameWindow::~GameWindow()
{
    if(model)
    {
        delete model;
    }
}

void GameWindow::clearWindow()
{
    system("cls");
}

void GameWindow::printTable(std::ostream &stream)
{
    model->print(stream);
                        
    /*stream << "\n";*/
    for(std::size_t i = 1; i < 9; ++i)
    stream << " " << i << " ";
}

void GameWindow::printError(std::ostream &stream)
{
    if(errorMessage != "")
    {
        stream << "\n\n\terror: " << errorMessage << "\n";
    }
    errorMessage = "";
}

void GameWindow::printInstruction(std::ostream &stream)
{
    if(instruction != "")
    {
        stream << "\n\n" << instruction << "\n";
    }
}

void GameWindow::printGameOver(std::ostream &stream)
{
    clearWindow();
    if(model->hasBlackWon())
    {
        stream << "BLACK WON\n";
        ofstream chss;
        chss.open ("who_won.txt");
        chss << "BLACK WON!!!\n";
        chss.close();
    }
    else
    {
        stream << "WHITE WON\n";
        ofstream chss;
        chss.open ("who_won.txt");
        chss << "WHITE WON!!!\n";
        chss.close();
    }
}

void GameWindow::selectPiece(std::ostream &stream)
{
    userInput.clear();
    std::cin >> userInput;
    bool errorHappened = true;

    try
    {
        model->selectPiece(userInput);
        instruction = "Select a field to step to";
        errorHappened = false;
    }
    catch(std::logic_error& e) 
    {
        errorMessage = e.what();    
    }

    print(stream);
    if(!errorHappened)
    {
        stepPiece(stream);
    }
    else
    {
        selectPiece(stream);
    }
}

void GameWindow::stepPiece(std::ostream &stream)
{
    userInput.clear();  
    std::cin >> userInput;
    bool gameOver = false;
    bool errorHappened = true;

    try
    {
        model->stepPiece(userInput);
        instruction = "Select a piece";
        gameOver = model->isGameOver();
        errorHappened = false;
    }
    catch(std::logic_error& e) 
    {
        errorMessage = e.what();
    }

    if(gameOver)
    {
        printGameOver(stream);
    }
    else
    {
        print(stream);
        if(errorHappened)
        {
            stepPiece(stream);
        }
        else
        {
            selectPiece(stream);
        }
    }
}

void GameWindow::print(std::ostream &stream)
{
    clearWindow();
    printTable(stream);
    printError(stream);
    printInstruction(stream);
}
