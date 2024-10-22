#include "Player.h"

Player::Player(int playerId, Color playerColor) 
    : id(playerId)
    , color(playerColor)
    , isCurrentTurn(false)
    , score(0) 
{}

int Player::getId() const {
    return id;
}

Color Player::getColor() const {
    return color;
}

bool Player::getIsCurrentTurn() const {
    return isCurrentTurn;
}

int Player::getScore() const {
    return score;
}

void Player::setTurn(bool isTurn) {
    isCurrentTurn = isTurn;
}

void Player::incrementScore() {
    score++;
}

void Player::resetScore() {
    score = 0;
}