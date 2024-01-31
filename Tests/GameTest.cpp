/**
 * @file GameTest.cpp
 * @author User
 */

#include "gtest/gtest.h"

#include <iostream>
#include <pch.h>
#include <Game.h>
#include <UMLData.h>
#include <UMLValue.h>

using namespace std;

const wxString file = L"data/uml.xml";

TEST(GameTest, ConstructTest)
{
    Game game;
}

TEST(GameTest, LoadTest)
{
    Game game;
    UMLData data = game.GetData();
    vector<UMLValue> goodNameVector = data.GetGoodName();

    ASSERT_EQ(goodNameVector.size(), 4);
    ASSERT_EQ(goodNameVector[0].GetName(), L"Employer");
    ASSERT_EQ(goodNameVector[3].GetName(), L"Actor");
    ASSERT_EQ(goodNameVector[3].GetDerived(), L"");

    vector<UMLValue> badNameVector = data.GetBadName();
    ASSERT_EQ(badNameVector.size(), 4);
    ASSERT_EQ(badNameVector[0].GetName(), L"employer");
    ASSERT_EQ(badNameVector[1].GetName(), L"");
    ASSERT_EQ(badNameVector[2].GetAttribute(), L"Should be capitalized");

    vector<UMLValue> goodAttributeVector = data.GetGoodAttribute();

    ASSERT_EQ(goodAttributeVector.size(), 6);
    ASSERT_EQ(goodAttributeVector[0].GetName(), L"age: int");
    ASSERT_EQ(goodAttributeVector[5].GetName(), L"angle: double=0");

    vector<UMLValue> badAttributeVector = data.GetBadAttribute();
    ASSERT_EQ(badAttributeVector.size(), 10);
    ASSERT_EQ(badAttributeVector[0].GetName(), L"mAge: int");
    ASSERT_EQ(badAttributeVector[8].GetName(), L"city: City");
    ASSERT_EQ(badAttributeVector[2].GetAttribute(), L"No spaces in names");

    vector<UMLValue> goodOperationVector = data.GetGoodOperation();

    ASSERT_EQ(goodOperationVector.size(), 7);
    ASSERT_EQ(goodOperationVector[0].GetName(), L"Save(filename: string)");
    ASSERT_EQ(goodOperationVector[5].GetName(), L"SetKeyframe(angle: double)");

    vector<UMLValue> badOperationVector = data.GetBadOperation();
    ASSERT_EQ(badOperationVector.size(), 3);
    ASSERT_EQ(badOperationVector[0].GetName(), L"GetActors(): vector<Actor>");
    ASSERT_EQ(badOperationVector[2].GetName(), L"Launchrocket(): bool");
    ASSERT_EQ(badOperationVector[1].GetAttribute(), L"Missing type");

    vector<UMLValue> goodInheritanceVector = data.GetGoodInheritance();

    ASSERT_EQ(goodInheritanceVector.size(), 3);
    ASSERT_EQ(goodInheritanceVector[1].GetBase(), L"Employee");
    ASSERT_EQ(goodInheritanceVector[1].GetDerived(), L"Manager");

    vector<UMLValue> badInheritanceVector = data.GetBadInheritance();
    ASSERT_EQ(badInheritanceVector.size(), 4);
    ASSERT_EQ(badInheritanceVector[0].GetBase(), L"StinkyFish");
    ASSERT_EQ(badInheritanceVector[1].GetDerived(), L"StinkyFish");
    ASSERT_EQ(badInheritanceVector[3].GetDirection(), L"down");
    ASSERT_EQ(badInheritanceVector[2].GetAttribute(), L"Can't say 'is a'");
}
 
