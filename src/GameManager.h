#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Player.h"
#include "Grid.h"
#include <array>
#include <plog/Log.h>

#define LCOV_EXCL_START
#define LCOV_EXCL_END
#define LCOV_EXCL_LINE

class GameManager {
private:
    std::array<Player, 2> players;
    Grid& grid;
    Player* currentPlayer;
    bool gameFinished;

    void switchPlayer();

public:
    GameManager(Grid& gameGrid);
    
    // Méthodes de logique de jeu (à tester)
    void handleTurn(int column);
    Player* getCurrentPlayer();
    void resetGame();
    bool isGameFinished() const;
    
    // Méthodes de rendu et d'événements (exclues de la couverture)

    void update();
    void handleMouseClick();
    void handleKeyPress();
    void handleRender() const;
    void renderPlayerInfo() const;
    void renderGameFinish() const;
    
};


#endif // GAME_MANAGER