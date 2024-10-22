#ifndef GRID_H
#define GRID_H
#pragma once

#include <vector>
#include "raylib.h"
#include <plog/Log.h>

#define LCOV_EXCL_START
#define LCOV_EXCL_END
#define LCOV_EXCL_LINE

class Grid
{

public:
    struct PlacementResult
    {
        bool success;   // Si la pièce a été placée
        bool isWinning; // Si ce placement crée une victoire

        PlacementResult(bool s = false, bool w = false)
            : success(s), isWinning(w) {}
    };

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
    PlacementResult placePiece(int col, int player);
    void clear();

    // Rendering methods
    LCOV_EXCL_START
    void render(Color player1Color, Color player2Color) const;
    int getColumnFromX(int mouseX) const; // Convert mouse X position to column
    LCOV_EXCL_END
    // winning checking methods

    bool hasWon(int player) const;
    bool checkDirection(int row, int col, int dirX, int dirY, int player) const;

    void printGrid() const;
    std::string getGridString() const;
    bool checkLine(int row, int col, int dirX, int dirY, int player) const;

private:
    static const int ROWS = 6;
    static const int COLS = 7;
    static const int CELL_SIZE = 80;
    static const int CIRCLE_RADIUS = 30;

    std::vector<std::vector<int>> slots; // 0 = empty, 1 = player 1, 2 = player 2

    // Position and size of the board
    int boardX;
    int boardY;
    int boardWidth;
    int boardHeight;

    
};

#endif // GRID_H
