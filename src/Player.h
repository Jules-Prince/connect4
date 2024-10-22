#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player {
private:
    int id;
    Color color;
    bool isCurrentTurn;
    int score;

public:
    Player(int playerId, Color playerColor);

    // Getters
    int getId() const;
    Color getColor() const;
    bool getIsCurrentTurn() const;
    int getScore() const;

    // Setters
    void setTurn(bool isTurn);
    void incrementScore();
    void resetScore();
};

#endif //PLAYER