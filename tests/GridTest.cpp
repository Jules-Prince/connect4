#include <gtest/gtest.h>
#include "Grid.h"

class GridTest : public ::testing::Test {
protected:
    Grid grid;
    GridTest() : grid(800, 600) {}
};

TEST_F(GridTest, InitialGridIsEmpty) {
    for (int row = 0; row < grid.getRows(); row++) {
        for (int col = 0; col < grid.getCols(); col++) {
            EXPECT_EQ(grid.getCell(row, col), 0);
        }
    }
}

TEST_F(GridTest, PlacePieceInValidColumn) {
    auto result = grid.placePiece(3, 1);
    EXPECT_TRUE(result.success);
    EXPECT_EQ(grid.getCell(5, 3), 1);  // Piece should be at bottom
}

TEST_F(GridTest, PlacementResultTest) {
    // Test placement normal
    auto result = grid.placePiece(0, 1);
    EXPECT_TRUE(result.success);
    EXPECT_FALSE(result.isWinning);
    
    // Test winning placement
    for (int col = 1; col < 4; col++) {
        result = grid.placePiece(col, 1);
        if (col < 3) {
            EXPECT_TRUE(result.success);
            EXPECT_FALSE(result.isWinning);
        } else {
            // Dernier placement qui crée la victoire
            EXPECT_TRUE(result.success);
            EXPECT_TRUE(result.isWinning);
        }
    }
    grid.printGrid();
}

TEST_F(GridTest, InvalidPlacementTest) {
    // Remplir une colonne
    for (int i = 0; i < 6; i++) {
        auto result = grid.placePiece(0, 1);
        EXPECT_TRUE(result.success);
    }
    
    // Tenter de placer dans une colonne pleine
    auto result = grid.placePiece(0, 1);
    EXPECT_FALSE(result.success);
    EXPECT_FALSE(result.isWinning);
    grid.printGrid();
}

TEST_F(GridTest, FullColumnDetection) {
    int col = 3;
    // Fill column
    for (int i = 0; i < grid.getRows(); i++) {
        auto result = grid.placePiece(col, 1);
        EXPECT_TRUE(result.success);
    }
    // Try to place one more piece
    auto result = grid.placePiece(col, 1);
    EXPECT_FALSE(result.success);
}

TEST_F(GridTest, HorizontalWinCheck) {
    // Place 4 pieces in a row
    Grid::PlacementResult result;
    for (int col = 0; col < 4; col++) {
        result = grid.placePiece(col, 1);
        EXPECT_TRUE(result.success);
        if (col == 3) {
            EXPECT_TRUE(result.isWinning);
        } else {
            EXPECT_FALSE(result.isWinning);
        }
    }
    grid.printGrid();
    EXPECT_TRUE(grid.hasWon(1));
    EXPECT_FALSE(grid.hasWon(2));
}

TEST_F(GridTest, VerticalWinCheck) {
    // Place 4 pieces in one column
    Grid::PlacementResult result;
    for (int i = 0; i < 4; i++) {
        result = grid.placePiece(0, 1);
        EXPECT_TRUE(result.success);
        if (i == 3) {
            EXPECT_TRUE(result.isWinning);
        } else {
            EXPECT_FALSE(result.isWinning);
        }
    }
    grid.printGrid();
    EXPECT_TRUE(grid.hasWon(1));
    EXPECT_FALSE(grid.hasWon(2));
}

TEST_F(GridTest, DiagonalDownRightWinCheck) {
    Grid::PlacementResult result;
    // Create diagonal win ↘
    for (int col = 0; col < 4; col++) {
        for (int i = 0; i < col; i++) {
            result = grid.placePiece(col, 2);
            EXPECT_TRUE(result.success);
            EXPECT_FALSE(result.isWinning);
        }
        result = grid.placePiece(col, 1);
        EXPECT_TRUE(result.success);
        if (col == 3) {
            EXPECT_TRUE(result.isWinning);
        } else {
            EXPECT_FALSE(result.isWinning);
        }
    }
    grid.printGrid();
    EXPECT_TRUE(grid.hasWon(1));
    EXPECT_FALSE(grid.hasWon(2));
}

TEST_F(GridTest, DiagonalUpRightWinCheck) {
    Grid::PlacementResult result;
    // Create diagonal win ↗
    for (int col = 0; col < 4; col++) {
        for (int i = 0; i < 3 - col; i++) {
            result = grid.placePiece(col, 2);
            EXPECT_TRUE(result.success);
            EXPECT_FALSE(result.isWinning);
        }
        result = grid.placePiece(col, 1);
        EXPECT_TRUE(result.success);
        if (col == 3) {
            EXPECT_TRUE(result.isWinning);
        } else {
            EXPECT_FALSE(result.isWinning);
        }
    }
    grid.printGrid();
    EXPECT_TRUE(grid.hasWon(1));
    EXPECT_FALSE(grid.hasWon(2));
}

TEST_F(GridTest, NoWinCheck) {
    // Place some pieces without winning
    auto r1 = grid.placePiece(0, 1);
    auto r2 = grid.placePiece(1, 2);
    auto r3 = grid.placePiece(2, 1);
    auto r4 = grid.placePiece(3, 2);
    
    EXPECT_TRUE(r1.success);
    EXPECT_TRUE(r2.success);
    EXPECT_TRUE(r3.success);
    EXPECT_TRUE(r4.success);
    EXPECT_FALSE(r1.isWinning);
    EXPECT_FALSE(r2.isWinning);
    EXPECT_FALSE(r3.isWinning);
    EXPECT_FALSE(r4.isWinning);
    
    grid.printGrid();
    EXPECT_FALSE(grid.hasWon(1));
    EXPECT_FALSE(grid.hasWon(2));
}

TEST_F(GridTest, MultipleWinsCheck) {
    Grid::PlacementResult result;
    // Create two winning combinations
    for (int col = 0; col < 4; col++) {
        result = grid.placePiece(col, 1);  // Horizontal win
        EXPECT_TRUE(result.success);
        result = grid.placePiece(0, 1);    // Also creating vertical win
        EXPECT_TRUE(result.success);
        if (col == 3 || (col == 2 && grid.getCell(0, 0) == 1)) {
            EXPECT_TRUE(result.isWinning);
        }
    }
    grid.printGrid();
    EXPECT_TRUE(grid.hasWon(1));
}

TEST_F(GridTest, CheckLineHorizontal) {
    
    // Set up a horizontal line of player 1 pieces
    grid.placePiece(0, 1);
    grid.placePiece(1, 1);
    grid.placePiece(2, 1);
    grid.placePiece(3, 1);
    
    // Check horizontal line (dirX=1, dirY=0)
    EXPECT_TRUE(grid.checkLine(5, 0, 1, 0, 1));  // Should find 4 in a row
    EXPECT_FALSE(grid.checkLine(5, 1, 1, 0, 1)); // Starting from second position should fail
    EXPECT_FALSE(grid.checkLine(5, 0, 1, 0, 2)); // Wrong player should fail
}

TEST_F(GridTest, CheckLineVertical) {
    
    // Set up a vertical line of player 2 pieces
    grid.placePiece(0, 2);
    grid.placePiece(0, 2);
    grid.placePiece(0, 2);
    grid.placePiece(0, 2);
    
    // Check vertical line (dirX=0, dirY=1)
    EXPECT_TRUE(grid.checkLine(2, 0, 0, 1, 2));  // Should find 4 in a row
    EXPECT_FALSE(grid.checkLine(3, 0, 0, 1, 2)); // Starting too late should fail
    EXPECT_FALSE(grid.checkLine(2, 0, 0, 1, 1)); // Wrong player should fail
}

TEST_F(GridTest, CheckLineDiagonalDownRight) {
    
    // Set up a diagonal line of player 1 pieces
    grid.placePiece(0, 1); // Column 0
    grid.placePiece(1, 2); // Column 1
    grid.placePiece(1, 1);
    grid.placePiece(2, 2); // Column 2
    grid.placePiece(2, 2);
    grid.placePiece(2, 1);
    grid.placePiece(3, 2); // Column 3
    grid.placePiece(3, 2);
    grid.placePiece(3, 2);
    grid.placePiece(3, 1);

    grid.printGrid();
    
    // Check diagonal line (dirX=1, dirY=1)
    EXPECT_TRUE(grid.checkLine(5, 0, 1, -1, 1));  // Should find 4 in a row
    EXPECT_FALSE(grid.checkLine(4, 0, 1, -1, 1)); // Starting from wrong position should fail
    EXPECT_FALSE(grid.checkLine(5, 0, 1, -1, 2)); // Wrong player should fail
}

TEST_F(GridTest, CheckLineDiagonalUpRight) {
    
    // Set up a diagonal line of player 2 pieces
    grid.placePiece(3, 2); // Column 0
    grid.placePiece(3, 2);
    grid.placePiece(3, 2);
    grid.placePiece(3, 2);
    grid.placePiece(2, 1); // Column 1
    grid.placePiece(2, 1);
    grid.placePiece(2, 2);
    grid.placePiece(1, 1); // Column 2
    grid.placePiece(1, 2);
    grid.placePiece(0, 2); // Column 3
    
    // Check diagonal line (dirX=1, dirY=-1)
    EXPECT_TRUE(grid.checkLine(5, 0, 1, -1, 2));  // Should find 4 in a row
    EXPECT_FALSE(grid.checkLine(4, 0, 1, -1, 2)); // Starting too low should fail
    EXPECT_FALSE(grid.checkLine(5, 0, 1, -1, 1)); // Wrong player should fail
}

TEST_F(GridTest, CheckLineOutOfBounds) {
    
    // Test checking beyond grid boundaries
    EXPECT_FALSE(grid.checkLine(5, 4, 1, 0, 1));  // Would go past right edge
    EXPECT_FALSE(grid.checkLine(2, 0, 0, -1, 1)); // Would go past top edge
    EXPECT_FALSE(grid.checkLine(0, 0, -1, 0, 1)); // Would go past left edge
    EXPECT_FALSE(grid.checkLine(2, 0, 0, 1, 1));  // Would go past bottom edge
}