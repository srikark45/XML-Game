/**
 * @file SpeedBoostTest.cpp
 * @author Zachary Troxell
 */



#include <pch.h>
#include <gtest/gtest.h>
#include <Game.h>
#include <Item.h>
#include <SpeedBoost.h>


TEST(SpeedBoostTest, Construct) {
    Game game;
    SpeedBoost SpeedBoost(&game);
}


TEST(SpeedBoostTest, HitTest) {
    // Create an item to test
    Game game;
    SpeedBoost boost(&game);

    // Give it a location
    // Always make the numbers different, in case they are mixed up
    boost.SetLocation(100, 200);


    // Our items should implement the HitTest since not all have images or set sizes
    // Center of the item should be a true
    ASSERT_TRUE(boost.HitTest(100, 200));

    // Left of the item
    ASSERT_FALSE(boost.HitTest(-200, 200));

    // Right of the item
    ASSERT_FALSE(boost.HitTest(400, 200));

    // Above the item
    ASSERT_FALSE(boost.HitTest(100, 0));

    // Below the item
    ASSERT_FALSE(boost.HitTest(100, 400));

    // On a boost transparent pixel
    ASSERT_FALSE(boost.HitTest(100 - 125/2 + 17, 200 - 117/2 + 16));
}

TEST(SpeedBoostTest, OutOfBounds) {
    // Create an item to test
    Game game;
    SpeedBoost boost(&game);

    // Give it a location
    boost.SetLocation(100, 200);


    // Test to see if when on the screen it is fine
    ASSERT_FALSE(boost.OutOfBounds());

    //very far to the right
    boost.SetLocation(1000000, 0);
    ASSERT_FALSE(boost.OutOfBounds());

    //very far to the left
    boost.SetLocation(-1000000, 0);
    ASSERT_FALSE(boost.OutOfBounds());

    // Fallen to the bottom
    boost.SetLocation(0, 1001);
    ASSERT_TRUE(boost.OutOfBounds());
}

