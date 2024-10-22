#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Player.h"
#include "Grid.h"
#include <array>
#include <plog/Log.h>

class GameManager {
private:
    std::array<Player, 2> players;
    Grid& grid;
    Player* currentPlayer;
    bool gameFinished;

    void switchPlayer();
    void handleMouseClick();
    void handleKeyPress();

public:
    GameManager(Grid& gameGrid);
    void update();
    
    // Game flow methods
    void handleTurn(int column);
    Player* getCurrentPlayer();
    void resetGame();
    bool isGameFinish() const;
    
    // Rendering
    void renderPlayerInfo() const;
    void renderGameFinish() const;
    void handleRender() const;
};

#endif //GAME_MANAGER