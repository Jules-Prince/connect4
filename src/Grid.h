#ifndef GRID_H
#define GRID_H
#pragma once

#include <vector>
#include "raylib.h"


class Grid {
private:
    static const int ROWS = 6;
    static const int COLS = 7;
    static const int CELL_SIZE = 80;
    static const int CIRCLE_RADIUS = 30;
    
    std::vector<std::vector<int>> slots;  // 0 = empty, 1 = player 1, 2 = player 2
    
    // Position and size of the board
    int boardX;
    int boardY;
    int boardWidth;
    int boardHeight;

public:
    Grid(int screenWidth, int screenHeight);
    
    // Getters for dimensions
    int getRows() const;
    int getCols() const;
    int getBoardX() const;
    int getBoardY() const;
    int getBoardWidth() const;
    int getBoardHeight() const;

    // Game logic methods
    int getCell(int row, int col) const;
    bool isValidPosition(int row, int col) const;
    int getLowestEmptyRow(int col) const;
    bool placePiece(int col, int player);
    bool isFull() const;
    void clear();

    // Rendering methods
    void render(Color player1Color, Color player2Color) const;
    int getColumnFromX(int mouseX) const;  // Convert mouse X position to column

    //winning checking methods
    bool checkWin(int row, int col, int player) const;
    bool checkDirection(int row, int col, int dirX, int dirY, int player) const;
};

#endif // GRID_H

