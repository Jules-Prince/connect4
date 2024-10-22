#include "GameManager.h"

GameManager::GameManager(Grid &gameGrid)
    : players{Player(1, RED), Player(2, YELLOW)}, grid(gameGrid), currentPlayer(&players[0]), gameFinished(false)
{
    players[0].setTurn(true);
    players[1].setTurn(false);
}

void GameManager::handleMouseClick()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        int column = grid.getColumnFromX(GetMousePosition().x);
        if (column != -1)
        {
            PLOGD << "Click detected in column " << column;
            handleTurn(column);
        }
    }
}

void GameManager::handleKeyPress()
{
    if (IsKeyPressed(KEY_R))
    {
        resetGame();
    }
}

void GameManager::update()
{
    handleMouseClick();
    handleKeyPress();
}

void GameManager::switchPlayer()
{
    currentPlayer->setTurn(false);
    currentPlayer = (currentPlayer == &players[0]) ? &players[1] : &players[0];
    currentPlayer->setTurn(true);
}

void GameManager::handleTurn(int column)
{
    if (gameFinished)
    {
        PLOGW << "Move attempted but game is over";
        return;
    }

    if (grid.placePiece(column, currentPlayer->getId()))
    {
        PLOGI << "Player " << currentPlayer->getId() << " placed piece in column " << column;
        // Pieced has been placed successfully
        if (grid.checkWin(grid.getLowestEmptyRow(column) + 1, column, currentPlayer->getId()))
        {
            gameFinished = true;
            currentPlayer->incrementScore();
            PLOGI << "Player " << currentPlayer->getId() << " wins! Score: " 
                  << players[0].getScore() << " - " << players[1].getScore();
            return;
        }
        switchPlayer();
        PLOGD << "Turn switched to Player " << currentPlayer->getId();
    } else {
        PLOGE << "Invalid move attempted in column " << column;
    }
}

void GameManager::resetGame()
{
    grid.clear();
    currentPlayer = &players[0];
    players[0].setTurn(true);
    players[1].setTurn(false);
    gameFinished = false;
    PLOGI << "Game reset. Scores: " << players[0].getScore() 
          << " - " << players[1].getScore();
}

bool GameManager::isGameFinish() const
{
    return gameFinished;
}

void GameManager::renderGameFinish() const
{
    const char *message = TextFormat("Player %d Wins! Press R to restart", currentPlayer->getId());
    int textWidth = MeasureText(message, 40);
    int textHeight = 40;

    int rectWidth = textWidth + 40;
    int rectHeight = textHeight + 40;

    int rectX = (GetScreenWidth() - rectWidth) / 2;
    int rectY = (GetScreenHeight() - rectHeight) / 2;

    Color semiTransparentBlack = {0, 0, 0, 200};
    DrawRectangle(rectX, rectY, rectWidth, rectHeight, semiTransparentBlack);

    DrawText(message,
             rectX + 20,
             rectY + 20,
             40,
             currentPlayer->getColor());
}

void GameManager::renderPlayerInfo() const
{
    // Draw current player indicator
    if (!gameFinished)
    {
        char message[32];
        snprintf(message, sizeof(message), "Player %d's Turn", currentPlayer->getId());
        DrawText(message, 10, 10, 20, BLACK);
    }

    // Draw scores
    char scoreMessage[32];
    snprintf(scoreMessage, sizeof(scoreMessage), "P1: %d | P2: %d",
             players[0].getScore(), players[1].getScore());
    DrawText(scoreMessage, 10, 40, 20, BLACK);
}

void GameManager::handleRender() const
{
    grid.render(players[0].getColor(), players[1].getColor());
    renderPlayerInfo();
    if (gameFinished)
    {
        renderGameFinish();
    }
}