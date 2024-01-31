/**
 * @file ItemTest.cpp
 * @author Zachary Troxell
 */

#include <pch.h>
#include <gtest/gtest.h>
#include <Game.h>
#include <Item.h>

class ItemMock : public Item {
        public:
    ItemMock(Game *game) : Item(game) {}
    void Accept(ItemVisitor *visitor) {}
};

TEST(ItemTest, Construct) {
    Game game;
    ItemMock item(&game);
}

TEST(ItemTest, GettersSetters){
    Game game;
    ItemMock item(&game);

    // Test initial values
    ASSERT_NEAR(0, item.GetX(), 0.0001);
    ASSERT_NEAR(0, item.GetY(), 0.0001);

    // Test SetLocation, GetX, and GetY
    item.SetLocation(10.5, 17.2);
    ASSERT_NEAR(10.5, item.GetX(), 0.0001);
    ASSERT_NEAR(17.2, item.GetY(), 0.0001);

    // Test a second time with different values
    item.SetLocation(-72, -107);
    ASSERT_NEAR(-72, item.GetX(), 0.0001);
    ASSERT_NEAR(-107, item.GetY(), 0.0001);
}

TEST(ItemTest, HitTest) {
    // Create an item to test
    Game game;
    ItemMock item(&game);

    // Give it a location
    // Always make the numbers different, in case they are mixed up
    item.SetLocation(100, 200);


    // All locations should be false since we don't know how big the item is
    // Our items should implement the HitTest since not all have images or set sizes
    // Center of the item should be a false
    ASSERT_FALSE(item.HitTest(100, 200));

    // Left of the item
    ASSERT_FALSE(item.HitTest(10, 200));

    // Right of the item
    ASSERT_FALSE(item.HitTest(200, 200));

    // Above the item
    ASSERT_FALSE(item.HitTest(100, 0));

    // Below the item
    ASSERT_FALSE(item.HitTest(100, 300));

}

TEST(ItemTest, GetGame){
    Game game;
    ItemMock item(&game);
    ASSERT_TRUE(&game == item.GetGame());
}