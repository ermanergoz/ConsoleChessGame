#ifndef GAMEMODEL_H
#define GAMEMODEL_H


#include "Piece.h"
#include "GameTable.h"
#include <vector>
#include <map>
#include <ostream>

class GameModel
{
private:
    std::map<Piece*, std::vector<GameTable::Position>> blackPieces;
    std::map<Piece*, std::vector<GameTable::Position>> whitePieces;
    bool gameInProgress;
    GameTable* gameTable;
    Piece::Player winner;
    Piece::Player whoseTurn;
    Piece* selectedPiece;

    std::vector<GameTable::Position> availableSteps(Piece* piece);
    bool canMove(Piece* piece) { return availableSteps(piece).size() != 0; }
    bool canMoveAny(Piece::Player player) const;
    bool isInCheck(Piece::Player player);
    bool isInCheckMate(Piece::Player player);

    void refreshAvailablePositions(Piece* piece);
    void refreshAllAvailablePositions(Piece::Player player);

    void setUpTable();

    void cleanUp();

    bool isValidPosition(const std::string& position);
    GameTable::Position stringToPosition(const std::string& position);

    bool isEnemyOfSelected(GameTable::Position position);

    std::vector<Piece*> getAllPieces(Piece::Player player);

    bool simulatedStepSuccessfully(GameTable::Position position, Piece* piece);
    bool isPieceOnTable(Piece* toCheck);

public:
    GameModel();
    ~GameModel();

    void print(std::ostream& stream);

    void startNewGame();
    bool isGameOver() { return gameInProgress && isInCheckMate(whoseTurn); }
    bool hasBlackWon() { return isGameOver() && winner == Piece::Player::BLACK; } 

    void selectPiece(const std::string& from); 
    void stepPiece(const std::string& to); 
    bool isPieceSelected() { return selectedPiece != nullptr; }

    std::vector<GameTable::Position> availableStepsForSelected() { return availableSteps(selectedPiece); } 
};



#endif // GAMEMODEL_H
