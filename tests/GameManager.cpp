#include <gtest/gtest.h>
#include "GameManager.h"
#include "Grid.h"

class GameManagerTest : public ::testing::Test {
protected:
    Grid grid;
    GameManager gameManager;

    GameManagerTest() 
        : grid(800, 600)
        , gameManager(grid) {}
};

TEST_F(GameManagerTest, InitialState) {
    // Test initial player
    EXPECT_EQ(gameManager.getCurrentPlayer()->getId(), 1);
    EXPECT_TRUE(gameManager.getCurrentPlayer()->getIsCurrentTurn());
    EXPECT_FALSE(gameManager.isGameFinished());
}

TEST_F(GameManagerTest, PlayerSwitch) {
    // Get initial player
    Player* initialPlayer = gameManager.getCurrentPlayer();
    int initialId = initialPlayer->getId();
    
    // Make a valid move
    gameManager.handleTurn(3);
    
    // Check player has switched
    Player* nextPlayer = gameManager.getCurrentPlayer();
    EXPECT_NE(nextPlayer->getId(), initialId);
    EXPECT_TRUE(nextPlayer->getIsCurrentTurn());
    EXPECT_FALSE(initialPlayer->getIsCurrentTurn());
}

TEST_F(GameManagerTest, InvalidMove) {
    // Get initial player
    Player* initialPlayer = gameManager.getCurrentPlayer();
    
    // Try invalid column
    gameManager.handleTurn(-1);
    
    // Player should not change
    EXPECT_EQ(gameManager.getCurrentPlayer(), initialPlayer);
}

TEST_F(GameManagerTest, WinningMove) {
    // Create a winning situation for player 1
    for (int col = 0; col < 3; col++) {
        gameManager.handleTurn(col);  // Player 1
        gameManager.handleTurn(col);  // Player 2
    }
    
    // Winning move for player 1
    Player* winningPlayer = gameManager.getCurrentPlayer();
    int initialScore = winningPlayer->getScore();
    
    gameManager.handleTurn(3);  // Should win
    
    EXPECT_TRUE(gameManager.isGameFinished());
    EXPECT_EQ(winningPlayer->getScore(), initialScore + 1);
}

TEST_F(GameManagerTest, NoMovesAfterGameOver) {
    // Create a winning situation
    for (int col = 0; col < 3; col++) {
        gameManager.handleTurn(col);  // Player 1
        gameManager.handleTurn(col);  // Player 2
    }
    gameManager.handleTurn(3);  // Winning move
    
    // Try to make moves after game over
    Player* finalPlayer = gameManager.getCurrentPlayer();
    gameManager.handleTurn(4);
    
    // State shouldn't change
    EXPECT_TRUE(gameManager.isGameFinished());
    EXPECT_EQ(gameManager.getCurrentPlayer(), finalPlayer);
}

TEST_F(GameManagerTest, GameReset) {
    // Play some moves
    gameManager.handleTurn(3);
    gameManager.handleTurn(3);
    
    // Reset game
    gameManager.resetGame();
    
    // Check reset state
    EXPECT_FALSE(gameManager.isGameFinished());
    EXPECT_EQ(gameManager.getCurrentPlayer()->getId(), 1);
    EXPECT_TRUE(gameManager.getCurrentPlayer()->getIsCurrentTurn());
    
    // Verify grid is empty
    for (int row = 0; row < grid.getRows(); row++) {
        for (int col = 0; col < grid.getCols(); col++) {
            EXPECT_EQ(grid.getCell(row, col), 0);
        }
    }
}

TEST_F(GameManagerTest, FullColumnHandling) {
    // Fill a column
    for (int i = 0; i < 6; i++) {
        gameManager.handleTurn(0);
    }
    
    // Get current player
    Player* playerBeforeFullColumn = gameManager.getCurrentPlayer();
    
    // Try to play in full column
    gameManager.handleTurn(0);
    
    // Player shouldn't change
    EXPECT_EQ(gameManager.getCurrentPlayer(), playerBeforeFullColumn);
}

TEST_F(GameManagerTest, ScoreTracking) {
    // Create multiple wins
    
    // First win
    for (int col = 0; col < 3; col++) {
        gameManager.handleTurn(col);  // Player 1
        gameManager.handleTurn(col);  // Player 2
    }
    gameManager.handleTurn(3);  // Player 1 wins
    int player1Score = gameManager.getCurrentPlayer()->getScore();
    EXPECT_EQ(player1Score, 1);
    
    // Reset and create second win
    gameManager.resetGame();
    for (int col = 0; col < 3; col++) {
        gameManager.handleTurn(6-col);  // Player 1
        gameManager.handleTurn(6-col);  // Player 2
    }
    gameManager.handleTurn(3);  // Player 1 wins again
    
    EXPECT_EQ(gameManager.getCurrentPlayer()->getScore(), player1Score + 1);
}

TEST_F(GameManagerTest, CompleteGameSimulation) {
    // Simulate a complete game with alternating moves
    bool gameWon = false;
    int moveCount = 0;
    const int maxMoves = grid.getRows() * grid.getCols();
    
    while (!gameWon && moveCount < maxMoves) {
        int col = moveCount % grid.getCols();
        gameManager.handleTurn(col);
        gameWon = gameManager.isGameFinished();
        moveCount++;
    }
    
    // Game should either be won or board should be full
    EXPECT_TRUE(gameWon || moveCount == maxMoves);
}