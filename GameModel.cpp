#include "GameModel.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"

GameModel::GameModel() : gameInProgress(false), gameTable(nullptr)
{
    startNewGame();
}

GameModel::~GameModel()
{
    cleanUp();
}

void GameModel::print(std::ostream &stream) 
{
    gameTable->print(stream);   
}

void GameModel::startNewGame()
{
    cleanUp();

    gameTable = new GameTable;
    whoseTurn = Piece::Player::WHITE;

    setUpTable();
    refreshAllAvailablePositions(Piece::Player::WHITE);

    gameInProgress = true;
}

void GameModel::selectPiece(const std::string &from)
{
    if(!gameInProgress)
    {
        throw std::logic_error("No game in progress.");
    }

    if(!isValidPosition(from))
    {
        throw std::invalid_argument("Not a valid position.");
    }

    auto candidate = gameTable->getPieceAt(stringToPosition(from)); 

    if(!candidate || candidate->getPlayer() != whoseTurn)
    {
        throw std::invalid_argument("Selected piece is not the current player's.");
    }

    if(!canMove(candidate)) 
    {
        throw std::invalid_argument("The selected piece cannot move.");
    }

    selectedPiece = candidate;
}

void GameModel::stepPiece(const std::string &to)
{
    if(!gameInProgress)
    {
        throw std::logic_error("No game in progress.");
    }
    if(!selectedPiece) 
    {
        throw std::logic_error("No selected piece.");
    }

    if(!isValidPosition(to))
    {
        throw std::invalid_argument("Not a valid position.");
    }

    GameTable::Position toStepTo = stringToPosition(to);

    auto availableSteps = availableStepsForSelected();  

    bool foundPosition = false; 

    for(const auto& availableStep : availableSteps)
    {
        if(availableStep == toStepTo)
        {
            foundPosition = true;
            break;
        }
    }

    if(!foundPosition)
    {
        throw std::invalid_argument("Piece cannot step there.");
    }

    if(isEnemyOfSelected(toStepTo)) 
    {
        auto takenPiece = gameTable->getPieceAt(toStepTo);
        delete takenPiece;

        if(selectedPiece->getPlayer() == Piece::Player::BLACK)
        {
            whitePieces.erase(takenPiece); 
        }
        else
        {
            blackPieces.erase(takenPiece);
        }
    }

    gameTable->setPieceTo(selectedPiece->getPosition(), nullptr);   
    gameTable->setPieceTo(toStepTo, selectedPiece); 

    refreshAllAvailablePositions(Piece::Player::WHITE);
    refreshAllAvailablePositions(Piece::Player::BLACK); 

    if(whoseTurn == Piece::Player::WHITE)
    {
        whoseTurn = Piece::Player::BLACK;
    }
    else
    {
        whoseTurn = Piece::Player::WHITE;
    }
}

std::vector<GameTable::Position> GameModel::availableSteps(Piece *piece)    
{
    if(!piece)
    {
        return std::vector<GameTable::Position>();  
    }

    if(piece->getPlayer() == Piece::Player::WHITE)
    {
        if(whitePieces.find(piece) == whitePieces.end()) 
        {
            throw std::invalid_argument("Piece is not on table.");
        }

        return whitePieces[piece];  
    }
    else
    {
        if(blackPieces.find(piece) == blackPieces.end())
        {
            throw std::invalid_argument("Piece is not on table.");
        }

        return blackPieces[piece];
    }
}

bool GameModel::canMoveAny(Piece::Player player) const
{
    if(player == Piece::Player::WHITE)  
    {
        for(const auto& piecePair : whitePieces) 
        {
            if(piecePair.second.size() > 0) 
            {
                return true;
            }
        }
    }
    else    
    {
        for(const auto& piecePair : blackPieces)
        {
            if(piecePair.second.size() > 0)
            {
                return true;
            }
        }
    }

    return false;
}

bool GameModel::isInCheck(Piece::Player player)
{
    if(player == Piece::Player::WHITE)  
    {
        GameTable::Position king;

        for(const auto& piecePair : whitePieces)    
        {
            if(dynamic_cast<King*>(piecePair.first)) 
            {                                           
                king = piecePair.first->getPosition();
                break;                                 
            }
        }

        for(auto& piece : getAllPieces(Piece::Player::BLACK))   
                                                                
        {
            if(isPieceOnTable(piece)) 
            {
                for(const auto& position : piece->availableSteps())
                {
                    if(position == king)    
                    {
                        return true; 
                    }
                }
            }
        }
        return false;
    }
    else
    {
        GameTable::Position king;

        for(const auto& piecePair : blackPieces)
        {
            if(dynamic_cast<King*>(piecePair.first))
            {
                king = piecePair.first->getPosition();
                break;
            }
        }

        for(auto& piece : getAllPieces(Piece::Player::WHITE))
        {
            if(isPieceOnTable(piece)) 
            {
                for(const auto& position : piece->availableSteps())
                {
                    if(position == king)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }

}

bool GameModel::isInCheckMate(Piece::Player player)
{
    if(isInCheck(player) && !canMoveAny(player))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void GameModel::refreshAvailablePositions(Piece *piece)
{
    bool inCheck = isInCheck(piece->getPlayer());

    if(piece->getPlayer() == Piece::Player::WHITE)
    {
        whitePieces[piece].clear();

        auto candidates = piece->availableSteps();  
                                                    
        if(dynamic_cast<King*>(piece) || inCheck)
        {
            for(auto& candidate : candidates)   
            {
                if(!dynamic_cast<King*>(gameTable->getPieceAt(candidate)) && simulatedStepSuccessfully(candidate, piece))
                {
                    whitePieces[piece].push_back(candidate);    
                }
            }
        }
        else
        {
            gameTable->setPieceTo(piece->getPosition(), nullptr); 
            if(!isInCheck(piece->getPlayer()))   
            {
                for(auto& candidate : candidates)
                {
                    if(!dynamic_cast<King*>(gameTable->getPieceAt(candidate)))
                    {
                        whitePieces[piece].push_back(candidate);
                    }
                }
            }
            

            gameTable->setPieceTo(piece->getPosition(), piece); 
        }
    }
    else
    {
        blackPieces[piece].clear();

        auto candidates = piece->availableSteps();

        if(dynamic_cast<King*>(piece) || inCheck)
        {
            for(auto& candidate : candidates)
            {
                if(!dynamic_cast<King*>(gameTable->getPieceAt(candidate)) && simulatedStepSuccessfully(candidate, piece))
                {
                    blackPieces[piece].push_back(candidate);
                }
            }
        }
        else
        {
            gameTable->setPieceTo(piece->getPosition(), nullptr); 
            if(!isInCheck(piece->getPlayer()))   
            {
                for(auto& candidate : candidates)
                {
                    if(!dynamic_cast<King*>(gameTable->getPieceAt(candidate)))
                    {
                        blackPieces[piece].push_back(candidate);
                    }
                }
            }
            

            gameTable->setPieceTo(piece->getPosition(), piece); 
        }
    }
}

void GameModel::refreshAllAvailablePositions(Piece::Player player)
{
    for(auto& piece : getAllPieces(player))
    {
        refreshAvailablePositions(piece);
    }
}

void GameModel::setUpTable()
{
    for(std::size_t col = 0; col < 8; ++col)
    {
        whitePieces[new Pawn(*gameTable, GameTable::Position(6, col), Piece::Player::WHITE)];
    }

     whitePieces[new Rook(*gameTable, GameTable::Position(7, 0), Piece::Player::WHITE)];
      whitePieces[new Rook(*gameTable, GameTable::Position(7, 7), Piece::Player::WHITE)];
       whitePieces[new Knight(*gameTable, GameTable::Position(7, 1), Piece::Player::WHITE)];
        whitePieces[new Knight(*gameTable, GameTable::Position(7, 6), Piece::Player::WHITE)];
         whitePieces[new Bishop(*gameTable, GameTable::Position(7, 2), Piece::Player::WHITE)];
          whitePieces[new Bishop(*gameTable, GameTable::Position(7, 5), Piece::Player::WHITE)];
          whitePieces[new Queen(*gameTable, GameTable::Position(7, 3), Piece::Player::WHITE)];
           whitePieces[new King(*gameTable, GameTable::Position(7, 4), Piece::Player::WHITE)];

    for(std::size_t col = 0; col < 8; ++col)
    {
        blackPieces[new Pawn(*gameTable, GameTable::Position(1, col), Piece::Player::BLACK)];
    }

    blackPieces[new Rook(*gameTable, GameTable::Position(0, 0), Piece::Player::BLACK)];
     blackPieces[new Rook(*gameTable, GameTable::Position(0, 7), Piece::Player::BLACK)];
      blackPieces[new Knight(*gameTable, GameTable::Position(0, 1), Piece::Player::BLACK)];
       blackPieces[new Knight(*gameTable, GameTable::Position(0, 6), Piece::Player::BLACK)];
        blackPieces[new Bishop(*gameTable, GameTable::Position(0, 2), Piece::Player::BLACK)];
         blackPieces[new Bishop(*gameTable, GameTable::Position(0, 5), Piece::Player::BLACK)];
         blackPieces[new Queen(*gameTable, GameTable::Position(0, 3), Piece::Player::BLACK)];
          blackPieces[new King(*gameTable, GameTable::Position(0, 4), Piece::Player::BLACK)];

    for(auto& piecePair : whitePieces)
    {
        gameTable->setPieceTo(piecePair.first->getPosition(), piecePair.first);
    }
    for(auto& piecePair : blackPieces)
    {
        gameTable->setPieceTo(piecePair.first->getPosition(), piecePair.first);
    }

}

void GameModel::cleanUp()   
{
    for(auto& pair : whitePieces)
    {
        delete pair.first;  
    }

    for(auto& pair : blackPieces)
    {
        delete pair.first;
    }

    whitePieces.clear();
    blackPieces.clear();

    if(gameTable)
    {
        delete gameTable;
    }

    selectedPiece = nullptr; 
    gameInProgress = false; 
}

bool GameModel::isValidPosition(const std::string &position)    
{
    if(position.size() != 2)
    {
        return false;
    }

    if(!(position[0] >= 'a' && position[0] <= 'h') && !(position[0] >= 'A' && position[0] <= 'H'))
    {
        return false;
    }

    if(!(position[1] >= '1' && position[1] <= '8'))
    {
        return false;
    }

    return true;
}

GameTable::Position GameModel::stringToPosition(const std::string &position)
{
    if(!isValidPosition(position))
    {
        throw std::invalid_argument("Not a valid position.");
    }

    std::size_t row, col;

    if(position[0] >= 'a' && position[0] <= 'h')
    {
        row = position[0] - 'a';
    }
    else
    {
        row = position[0] - 'A';
    }

    col = position[1] - '1';

    return GameTable::Position(row, col);
}

bool GameModel::isEnemyOfSelected(GameTable::Position position)
{
    if(!selectedPiece)
    {
        throw std::logic_error("No selected piece");
    }

    if(gameTable->getPieceAt(position) && gameTable->getPieceAt(position)->getPlayer() != selectedPiece->getPlayer())
    {
        return true;
    }

    return false;
}

std::vector<Piece *> GameModel::getAllPieces(Piece::Player player)
{
    std::vector<Piece *> pieces;

    if(player == Piece::Player::WHITE)
    {
        for(auto& piecePair : whitePieces)
        {
            pieces.push_back(piecePair.first);
        }
    }
    else
    {
        for(auto& piecePair : blackPieces)
        {
            pieces.push_back(piecePair.first);
        }
    }

    return pieces;
}

bool GameModel::simulatedStepSuccessfully(GameTable::Position position, Piece* piece)   
{   
    GameTable::Position originalPosition = piece->getPosition();
    Piece* originalPiece = gameTable->getPieceAt(position);
    gameTable->setPieceTo(position, piece);

    if(isInCheck(piece->getPlayer()))
    {
        gameTable->setPieceTo(originalPosition, piece);
        gameTable->setPieceTo(position, originalPiece);
        return false;
    }
    else
    {
        gameTable->setPieceTo(originalPosition, piece);
        gameTable->setPieceTo(position, originalPiece);
        return true;
    }
}

bool GameModel::isPieceOnTable(Piece* toCheck)  
{
    if(!toCheck)    
    {
        return false;
    }

    for(std::size_t row = 0; row < gameTable->getHeight(); ++row)
    {
        for(std::size_t col = 0; col < gameTable->getWidth(); ++col)
        {
            if(toCheck == gameTable->getPieceAt(GameTable::Position(row, col)))
            {
                return true;
            }
        }
    }
    return false;
}
