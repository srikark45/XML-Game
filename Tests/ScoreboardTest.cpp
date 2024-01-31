/**
 * @file ScoreboardTest.cpp
 * @author Ian Hay
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <Scoreboard.h>



TEST(ScoreboardTest, Construct)
{
    Game game;
    Scoreboard board(&game);
}

TEST(ScoreboardTest, incrementTest)
{
    Game game;
    Scoreboard board(&game);

    board.IncCorrect();
    ASSERT_EQ(board.GetCorrect(), 1);
    ASSERT_EQ(board.GetMissed(), 0);
    ASSERT_EQ(board.GetUnfair(), 0);

    board.IncMissed();
    ASSERT_EQ(board.GetCorrect(), 1);
    ASSERT_EQ(board.GetMissed(), 1);
    ASSERT_EQ(board.GetUnfair(), 0);

    board.IncUnfair();
    ASSERT_EQ(board.GetCorrect(), 1);
    ASSERT_EQ(board.GetMissed(), 1);
    ASSERT_EQ(board.GetUnfair(), 1);
}

TEST(ScoreboardTest, getterTest)
{
    Game game;
    Scoreboard board(&game);

    ASSERT_EQ(board.GetX(), 0);
    ASSERT_EQ(board.GetY(), 0);
    ASSERT_EQ(board.GetCorrect(), 0);
    ASSERT_EQ(board.GetMissed(), 0);
    ASSERT_EQ(board.GetUnfair(), 0);
}