#include <gtest/gtest.h>
#include "Player.h"

class PlayerTest : public ::testing::Test {
protected:
    Player player1;
    Player player2;

    PlayerTest() 
        : player1(1, RED)
        , player2(2, YELLOW) {}
};

TEST_F(PlayerTest, PlayerInitialization) {
    // Test player 1
    EXPECT_EQ(player1.getId(), 1);
    EXPECT_EQ(player1.getScore(), 0);
    EXPECT_FALSE(player1.getIsCurrentTurn());
    
    // Test player 2
    EXPECT_EQ(player2.getId(), 2);
    EXPECT_EQ(player2.getScore(), 0);
    EXPECT_FALSE(player2.getIsCurrentTurn());
}

TEST_F(PlayerTest, ColorAssignment) {
    // Test player 1 color (RED)
    Color p1Color = player1.getColor();
    EXPECT_EQ(static_cast<int>(p1Color.r), static_cast<int>(RED.r));
    EXPECT_EQ(static_cast<int>(p1Color.g), static_cast<int>(RED.g));
    EXPECT_EQ(static_cast<int>(p1Color.b), static_cast<int>(RED.b));
    EXPECT_EQ(static_cast<int>(p1Color.a), static_cast<int>(RED.a));
    
    // Test player 2 color (YELLOW)
    Color p2Color = player2.getColor();
    EXPECT_EQ(static_cast<int>(p2Color.r), static_cast<int>(YELLOW.r));
    EXPECT_EQ(static_cast<int>(p2Color.g), static_cast<int>(YELLOW.g));
    EXPECT_EQ(static_cast<int>(p2Color.b), static_cast<int>(YELLOW.b));
    EXPECT_EQ(static_cast<int>(p2Color.a), static_cast<int>(YELLOW.a));
}

TEST_F(PlayerTest, ScoreManagement) {
    // Test initial score
    EXPECT_EQ(player1.getScore(), 0);
    
    // Test increment
    player1.incrementScore();
    EXPECT_EQ(player1.getScore(), 1);
    
    // Test multiple increments
    player1.incrementScore();
    player1.incrementScore();
    EXPECT_EQ(player1.getScore(), 3);
    
    // Test reset
    player1.resetScore();
    EXPECT_EQ(player1.getScore(), 0);
}

TEST_F(PlayerTest, TurnManagement) {
    // Test initial turn state
    EXPECT_FALSE(player1.getIsCurrentTurn());
    EXPECT_FALSE(player2.getIsCurrentTurn());
    
    // Test setting turn for player 1
    player1.setTurn(true);
    EXPECT_TRUE(player1.getIsCurrentTurn());
    EXPECT_FALSE(player2.getIsCurrentTurn());
    
    // Test switching turn to player 2
    player1.setTurn(false);
    player2.setTurn(true);
    EXPECT_FALSE(player1.getIsCurrentTurn());
    EXPECT_TRUE(player2.getIsCurrentTurn());
}

TEST_F(PlayerTest, MultipleScoreIncrements) {
    // Simulate a game with multiple wins
    for (int i = 0; i < 5; i++) {
        player1.incrementScore();
    }
    for (int i = 0; i < 3; i++) {
        player2.incrementScore();
    }
    
    EXPECT_EQ(player1.getScore(), 5);
    EXPECT_EQ(player2.getScore(), 3);
    
    // Reset both scores
    player1.resetScore();
    player2.resetScore();
    
    EXPECT_EQ(player1.getScore(), 0);
    EXPECT_EQ(player2.getScore(), 0);
}

TEST_F(PlayerTest, AlternatingTurns) {
    // Simulate several turn alternations
    player1.setTurn(true);
    EXPECT_TRUE(player1.getIsCurrentTurn());
    EXPECT_FALSE(player2.getIsCurrentTurn());
    
    player1.setTurn(false);
    player2.setTurn(true);
    EXPECT_FALSE(player1.getIsCurrentTurn());
    EXPECT_TRUE(player2.getIsCurrentTurn());
    
    player2.setTurn(false);
    player1.setTurn(true);
    EXPECT_TRUE(player1.getIsCurrentTurn());
    EXPECT_FALSE(player2.getIsCurrentTurn());
}

TEST_F(PlayerTest, SimulateGameSession) {
    // Simulate a complete game session
    player1.setTurn(true);  // Player 1 starts
    
    // Some moves happen...
    player1.setTurn(false);
    player2.setTurn(true);
    
    // Player 1 wins
    player1.incrementScore();
    
    // New game starts...
    player2.setTurn(false);
    player1.setTurn(true);
    
    // Player 2 wins
    player2.incrementScore();
    
    // Verify final state
    EXPECT_EQ(player1.getScore(), 1);
    EXPECT_EQ(player2.getScore(), 1);
    EXPECT_TRUE(player1.getIsCurrentTurn());
    EXPECT_FALSE(player2.getIsCurrentTurn());
}