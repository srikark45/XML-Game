/**
 * @file DropDownTest.cpp
 * @author Nathaniel
 */

#include <gtest/gtest.h>

#include <pch.h>
#include <Game.h>
#include <DropDown.h>
#include <UMLData.h>
#include <UMLValue.h>

TEST(DropDownTest, BadTest) {
    Game game;

    /// Due to randomness this test will be repeated 100 times to be thorough
    for (int i = 0; i < 100; i++) {
        DropDown dropDown(&game);

        /// If dropDown is bad, then it should have one content that is bad

        std::vector<UMLValue> contentVector = dropDown.GetContent();
        bool bad = false;

        for (auto content: contentVector) {
            if (content.GetAttribute()!=L"") {
                bad = true;
            }
        }

        if (dropDown.GetBadness()) {
            ASSERT_TRUE(bad);
        }
        else {
            ASSERT_FALSE(bad);
        }
    }
}