#include "Grid.h"
#include "raylib.h"
#include <algorithm>
#include <iostream>

Grid::Grid(int screenWidth, int screenHeight) : slots(ROWS, std::vector<int>(COLS, 0)) {
    boardWidth = COLS * CELL_SIZE;
    boardHeight = ROWS * CELL_SIZE;
    boardX = (screenWidth - boardWidth) / 2;
    boardY = (screenHeight - boardHeight) / 2;
}

int Grid::getRows() const { return ROWS; }
int Grid::getCols() const { return COLS; }
int Grid::getBoardX() const { return boardX; }
int Grid::getBoardY() const { return boardY; }
int Grid::getBoardWidth() const { return boardWidth; }
int Grid::getBoardHeight() const { return boardHeight; }

int Grid::getCell(int row, int col) const {
    if (isValidPosition(row, col)) {
        return slots[row][col];
    }
    return -1;
}

bool Grid::isValidPosition(int row, int col) const {
    return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}

int Grid::getLowestEmptyRow(int col) const {
    if (col < 0 || col >= COLS) return -1;
    
    for (int row = ROWS - 1; row >= 0; row--) {
        if (slots[row][col] == 0) {
            return row;
        }
    }
    return -1;
}

bool Grid::placePiece(int col, int player) {
    int row = getLowestEmptyRow(col);
    if (row != -1) {
        slots[row][col] = player;
        
        if (checkWin(row, col, player)) {
            std::cout << "Player " << player << " wins!" << std::endl;
            return true;
        }
        return true;
    }
    return false;
}

bool Grid::isFull() const {
    for (int col = 0; col < COLS; col++) {
        if (getLowestEmptyRow(col) != -1) {
            return false;
        }
    }
    return true;
}

void Grid::clear() {
    for (auto& row : slots) {
        std::fill(row.begin(), row.end(), 0);
    }
}

void Grid::render(Color player1Color, Color player2Color) const {
    // Draw the board
    DrawRectangle(boardX, boardY, boardWidth, boardHeight, BLUE);

    // Draw the pieces
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            int centerX = boardX + col * CELL_SIZE + CELL_SIZE / 2;
            int centerY = boardY + row * CELL_SIZE + CELL_SIZE / 2;
            
            Color pieceColor;
            switch (slots[row][col]) {
                case 0:  // Empty
                    pieceColor = WHITE;
                    break;
                case 1:  // Player 1
                    pieceColor = player1Color;
                    break;
                case 2:  // Player 2
                    pieceColor = player2Color;
                    break;
                default:
                    pieceColor = WHITE;
            }
            DrawCircle(centerX, centerY, CIRCLE_RADIUS, pieceColor);
        }
    }
}

int Grid::getColumnFromX(int mouseX) const {
    if (mouseX >= boardX && mouseX < boardX + boardWidth) {
        return (mouseX - boardX) / CELL_SIZE;
    }
    return -1;
}

bool Grid::checkDirection(int row, int col, int dirX, int dirY, int player) const {
    int count = 0;
    
    // Vérifie 4 positions dans la direction donnée
    for (int i = 0; i < 4; i++) {
        int newRow = row + i * dirY;
        int newCol = col + i * dirX;
        
        if (!isValidPosition(newRow, newCol) || slots[newRow][newCol] != player) {
            return false;
        }
        count++;
    }
    
    return count == 4;
}

bool Grid::checkWin(int row, int col, int player) const {
    // Vérifie toutes les directions possibles
    // Horizontal (→)
    if (checkDirection(row, col, 1, 0, player)) return true;
    
    // Vertical (↓)
    if (checkDirection(row, col, 0, 1, player)) return true;
    
    // Diagonal (↘)
    if (checkDirection(row, col, 1, 1, player)) return true;
    
    // Diagonal (↗)
    if (checkDirection(row, col, 1, -1, player)) return true;
    
    return false;
}