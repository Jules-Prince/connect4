#include "Grid.h"
#include "raylib.h"
#include <algorithm>
#include <iostream>
#include <sstream>

Grid::Grid(int screenWidth, int screenHeight) : slots(ROWS, std::vector<int>(COLS, 0))
{
    boardWidth = COLS * CELL_SIZE;
    boardHeight = ROWS * CELL_SIZE;
    boardX = (screenWidth - boardWidth) / 2;
    boardY = (screenHeight - boardHeight) / 2;
}

LCOV_EXCL_START
int Grid::getRows() const { return ROWS; }
int Grid::getCols() const { return COLS; }
int Grid::getBoardX() const { return boardX; }
int Grid::getBoardY() const { return boardY; }
int Grid::getBoardWidth() const { return boardWidth; }
int Grid::getBoardHeight() const { return boardHeight; }
LCOV_EXCL_END

int Grid::getCell(int row, int col) const
{
    if (isValidPosition(row, col))
    {
        return slots[row][col];
    }
    return -1;
}

bool Grid::isValidPosition(int row, int col) const
{
    return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}

int Grid::getLowestEmptyRow(int col) const
{
    if (col < 0 || col >= COLS)
        return -1;

    for (int row = ROWS - 1; row >= 0; row--)
    {
        if (slots[row][col] == 0)
        {
            return row;
        }
    }
    return -1;
}

Grid::PlacementResult Grid::placePiece(int col, int player) {
    int row = getLowestEmptyRow(col);
    if (row != -1) {
        slots[row][col] = player;
        PLOGD << "Piece placed at (" << row << "," << col << ") for player " << player;
        
        bool winning = hasWon(player);
        return PlacementResult(true, winning);
    }
    return PlacementResult(false, false);
}

void Grid::clear()
{
    for (auto &row : slots)
    {
        std::fill(row.begin(), row.end(), 0);
    }
}




bool Grid::checkLine(int row, int col, int dirX, int dirY, int player) const
{
    int count = 0;

    for (int i = 0; i < 4; i++)
    {
        int newRow = row + (i * dirY);
        int newCol = col + (i * dirX);

        if (!isValidPosition(newRow, newCol) || slots[newRow][newCol] != player)
        {
            return false;
        }
        count++;
    }
    return count == 4;
}

bool Grid::hasWon(int player) const
{
    PLOGI << "Checking if player " << player << " has won";
    PLOGI << "Current slots state:\n"
          << getGridString();

    // Check horizontal (seulement de gauche à droite)
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col <= COLS - 4; col++)
        {
            if (slots[row][col] == player && checkLine(row, col, 1, 0, player))
            {
                PLOGI << "Horizontal win found at (" << row << "," << col << ")";
                return true;
            }
        }
    }

    // Check vertical (seulement de bas en haut)
    for (int col = 0; col < COLS; col++)
    {
        for (int row = 0; row <= ROWS - 4; row++)
        {
            if (slots[row][col] == player && checkLine(row, col, 0, 1, player))
            {
                PLOGI << "Vertical win found at (" << row << "," << col << ")";
                return true;
            }
        }
    }

    // Check diagonal ↘
    for (int row = 0; row <= ROWS - 4; row++)
    {
        for (int col = 0; col <= COLS - 4; col++)
        {
            if (slots[row][col] == player && checkLine(row, col, 1, 1, player))
            {
                PLOGI << "Diagonal down-right win found at (" << row << "," << col << ")";
                return true;
            }
        }
    }

    // Check diagonal ↗
    for (int row = 3; row < ROWS; row++)
    {
        for (int col = 0; col <= COLS - 4; col++)
        {
            if (slots[row][col] == player && checkLine(row, col, 1, -1, player))
            {
                PLOGI << "Diagonal up-right win found at (" << row << "," << col << ")";
                return true;
            }
        }
    }

    PLOGI << "No win found for player " << player;
    return false;
}



LCOV_EXCL_START
void Grid::render(Color player1Color, Color player2Color) const
{
    // Draw the board
    DrawRectangle(boardX, boardY, boardWidth, boardHeight, BLUE);

    // Draw the pieces
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            int centerX = boardX + col * CELL_SIZE + CELL_SIZE / 2;
            int centerY = boardY + row * CELL_SIZE + CELL_SIZE / 2;

            Color pieceColor;
            switch (slots[row][col])
            {
            case 0: // Empty
                pieceColor = WHITE;
                break;
            case 1: // Player 1
                pieceColor = player1Color;
                break;
            case 2: // Player 2
                pieceColor = player2Color;
                break;
            default:
                pieceColor = WHITE;
            }
            DrawCircle(centerX, centerY, CIRCLE_RADIUS, pieceColor);
        }
    }
}

int Grid::getColumnFromX(int mouseX) const
{
    if (mouseX >= boardX && mouseX < boardX + boardWidth)
    {
        return (mouseX - boardX) / CELL_SIZE;
    }
    return -1;
}

void Grid::printGrid() const
{
    std::cout << getGridString();
}

std::string Grid::getGridString() const
{
    std::stringstream ss;

    // Print column numbers
    ss << "\n ";
    for (int col = 0; col < COLS; col++)
    {
        ss << " " << col << " ";
    }
    ss << "\n";

    // Print top border
    ss << " ";
    for (int col = 0; col < COLS; col++)
    {
        ss << "---";
    }
    ss << "-\n";

    // Print slots content
    for (int row = 0; row < ROWS; row++)
    {
        ss << "|";
        for (int col = 0; col < COLS; col++)
        {
            char symbol;
            switch (slots[row][col])
            {
            case 0:
                symbol = ' ';
                break;
            case 1:
                symbol = 'R'; // Red player
                break;
            case 2:
                symbol = 'Y'; // Yellow player
                break;
            default:
                symbol = '?';
            }
            ss << " " << symbol << " ";
        }
        ss << "|\n";
    }

    // Print bottom border
    ss << " ";
    for (int col = 0; col < COLS; col++)
    {
        ss << "---";
    }
    ss << "-\n";

    return ss.str();
}

LCOV_EXCL_END