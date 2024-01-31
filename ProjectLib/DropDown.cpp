/**
 * @file DropDown.cpp
 * @author Team Grady Wins (Srikar Kante)
 */

#include "pch.h"

#include <cstdlib>
#include <memory>
#include <set>

#include "UMLData.h"
#include "UMLValue.h"
#include "Game.h"
#include "DropDown.h"
#include "Message.h"

using namespace std;

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedX = 10;

/// Minimum speed in the X direction in
/// pixels per second
const double MinSpeedX = -10;

/// Starting speed in the Y direction in
/// pixels per second
const double MinSpeedY = 30;

/// The background color of the dropdown box
const wxColour backgroundColor = wxColour(255, 255, 193);

/// Size of the font in y direction
const int FontSize = 15;

/// Number of different ways to be  "Bad"
const int WaysToBeBad = 5;

/// For use of randomization.  When randomizer gives a value equal
/// to this one it indicates a bad name.
const int NameIsBad = 0;

/// For use of randomization.  When randomizer gives a value equal
/// to this one it indicates a bad name.
const int AttributeOneIsBad = 1;

/// For use of randomization.  When randomizer gives a value equal
/// to this one it indicates a bad name.
const int AttributeTwoIsbad = 2;

/// For use of randomization.  When randomizer gives a value equal
/// to this one it indicates a bad name.
const int OperationOneIsBad = 3;

/// For use of randomization.  When randomizer gives a value equal
/// to this one it indicates a bad name.
const int OperationTwoIsBad = 4;

/// The padding for drawing the box
const int Padding = 3;

/// The size of the arrow
const int ArrowHeadSize = 10;

/// The size of the arrow
const int ArrowSize = 30;

/// Size of the arrow without the head
const int HeadlessArrow = 20;

/// Inheritance chance
const int InheritanceChance = 4;

/// Speed multiplier
const int SpeedFactor = 5;

/// Number of slots on a DropDown box
const int Slots = 4;

/// Number of attributes on a DropDown box
const int AttributeSlots = 2;

/// Decrease speed divisor
const int DecreaseSpeedDivisor = 3;

/// Slow factor when going toward the edge of the screen
const double SlowSpeed = .99;

/**
 * Constructor
 * @param game Game this scoreboard is a member of
 */
DropDown::DropDown(Game *game) : Item(game)
{
    // Setting the X speed of the Drop boxes
    std::uniform_real_distribution<> distribution1(MinSpeedX, MaxSpeedX);
    mSpeedX = distribution1(game->GetRandom());

    // Setting the Y speed of the Drop boxes
    double acceleration = game->GetElapsed() / SpeedFactor;
    mSpeedY = MinSpeedY + acceleration;

    // Setting the inheritance box probability
    std::uniform_int_distribution<> distributionBasic(0, InheritanceChance);

    auto test = distributionBasic(game->GetRandom());
    mBasic = test != InheritanceChance;

    if (mBasic)
    {
        InitiateBasic(game);
    }
    else
    {
        InitiateInheritance(game);
    }
}

/**
 * Update dropdown boxes
 * @param elapsed time that has passed
 */
void DropDown::Update(double elapsed)
{
    if (GetX() - mMaxWidth / 2 < -(GetGame() -> Width) / 2)
    {
        SetLocation( -(GetGame() -> Width) / 2 + mMaxWidth / 2, GetY() + mSpeedY * elapsed);
        return;
    }
    else if (GetX() + mMaxWidth / 2 > GetGame() -> Width / 2)
    {
        SetLocation(GetGame() -> Width / 2 - mMaxWidth / 2, GetY() + mSpeedY * elapsed);
        return;
    }
    if (GetX() > GetGame() -> Width / DecreaseSpeedDivisor && mSpeedX > 0)
    {
        mSpeedX = mSpeedX * SlowSpeed;
    }
    if (GetX() < -(GetGame() -> Width) / DecreaseSpeedDivisor && mSpeedX < 0)
    {
        mSpeedX = mSpeedX * SlowSpeed;
    }
    SetLocation(GetX() + mSpeedX * elapsed,
            GetY() + mSpeedY * elapsed);
    Item::Update(elapsed);

}

void DropDown::Draw(wxGraphicsContext *graphics)
{
    // Set up rectangle creation brush / pen
    wxBrush brush(backgroundColor);
    graphics->SetBrush(brush);
    wxPen pen(*wxBLACK);
    graphics->SetPen(pen);

    // Set up font
    wxFont font(wxSize(0, FontSize),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_THIN);
    graphics->SetFont(font, *wxBLACK);

    if (mBasic)
    {
        DrawBasic(graphics);
    }
    else
    {
        DrawInheritance(graphics);
    }

    graphics->GetWindow()->Update();
}

void DropDown::InitiateInheritance(Game *game)
{
    // Get mData in order to load in UML texts
    UMLData mData = game->GetData();

    // Initialize random seed
    srand(time(nullptr));


    mBad = (rand() % 2) == 1;

    int index;
    std::vector<UMLValue> inheritanceValues;
    if (mBad)
    {
        inheritanceValues = mData.GetBadInheritance();
    }
    else
    {
        inheritanceValues = mData.GetGoodInheritance();
    }
    index = rand() % inheritanceValues.size();
    mInheritance = inheritanceValues[index];

    // From now on the content may or may not exist, will use a 50% chance
    // Attributes
    bool exist;
    set<int> oldGood;
    std::vector<UMLValue> attributeValues;

    for (int i = 1; i <= Slots; i++)
    {
        exist = (rand() % 2) == 1;
        attributeValues = mData.GetGoodAttribute();
        if (exist)
        {
            index = rand() % attributeValues.size();
            while (oldGood.find(index) != oldGood.end())
            {
                index = rand() % attributeValues.size();
            }
            if (i <= AttributeSlots)
            {
                mAttributes.push_back(attributeValues[index]);
            }
            else
            {
                mSecondaryAttributes.push_back(attributeValues[index]);
            }
        }
    }

    // Operations
    oldGood.clear();
    std::vector<UMLValue> operationValues;
    for (int i = 1; i <= Slots; i++)
    {
        exist = (rand() % 2) == 1;
        operationValues = mData.GetGoodOperation();
        if (exist)
        {
            index = rand() % operationValues.size();
            while (oldGood.find(index) != oldGood.end())
            {
                index = rand() % operationValues.size();
            }
            if (i <= AttributeSlots)
            {
                mOperations.push_back(operationValues[index]);
            }
            else
            {
                mSecondaryOperations.push_back(operationValues[index]);
            }
        }
    }

}

void DropDown::DrawInheritance(wxGraphicsContext *graphics)
{
    // Determine width and height of boxes by finding longest content text
    double wid, hit;
    double attributeHit = 0;
    double operationHit = 0;
    double width = 0;
    graphics->GetTextExtent(mInheritance.GetBase(), &wid, &hit);
    if (wid>width) { width = wid; }
    for (auto attributeContent: mAttributes)
    {
        graphics->GetTextExtent(attributeContent.GetName(), &wid, &attributeHit);
        if (wid>width) { width = wid; }
    }
    for (auto operationContent: mOperations)
    {
        graphics->GetTextExtent(operationContent.GetName(), &wid, &operationHit);
        if (wid>width) { width = wid; }
    }

    // Add some padding
    width += Padding;

    // First print out the base box
    double nameHit;
    graphics->GetTextExtent(mInheritance.GetBase(), &wid, &nameHit);
    nameHit += Padding;
    graphics->DrawRectangle(GetX() - mMaxWidth / 2, GetY() - mHeight / 2, width + Padding, nameHit);
    graphics->DrawText(mInheritance.GetBase(), GetX() + Padding + ((width - wid) / 2) - mMaxWidth / 2, GetY() + Padding - mHeight / 2);

    int attributeSize = mAttributes.size();
    attributeHit += Padding;

    // Special case, no attributes and operations
    if (mAttributes.empty() && mOperations.empty())
    {
        attributeSize = 2;
    }
    graphics->DrawRectangle(GetX() - mMaxWidth / 2, GetY() + nameHit - mHeight / 2, width + Padding, attributeHit * attributeSize);
    int i = 0;
    for (auto attributeContent: mAttributes)
    {
        graphics->DrawText(attributeContent.GetName(), GetX() + Padding - mMaxWidth / 2, GetY() + nameHit +
                           (attributeHit * i) - mHeight / 2);
        i++;
    }

    int operationSize = mOperations.size();
    operationHit += Padding;
    graphics->DrawRectangle(GetX() - mMaxWidth / 2, GetY() + nameHit + (attributeHit * attributeSize) - mHeight / 2,
                            width + Padding,
            operationHit * operationSize);
    i = 0;
    for (auto operationContent: mOperations)
    {
        graphics->DrawText(operationContent.GetName(), GetX() + Padding - mMaxWidth / 2,
                GetY() + nameHit + (attributeHit * attributeSize) + (operationHit * i) - mHeight / 2);
        i++;
    }
    int baseBoxHeight = operationHit * operationSize + nameHit + attributeHit * attributeSize;

    mMaxWidth = width;

    // Draw out the inheritance arrow
    if (mInheritance.GetDirection()=="down")
    {
        graphics->StrokeLine(GetX(), GetY() + (baseBoxHeight) - mHeight / 2, GetX(), GetY() + (baseBoxHeight)
                              + HeadlessArrow - mHeight / 2);
        graphics->StrokeLine(GetX(), GetY() + baseBoxHeight - mHeight / 2 + ArrowSize, GetX() - ArrowHeadSize,
                             GetY() + (baseBoxHeight) + HeadlessArrow - mHeight / 2);
        graphics->StrokeLine(GetX(), GetY() + baseBoxHeight - mHeight / 2 + ArrowSize, GetX() + ArrowHeadSize,
                             GetY() + (baseBoxHeight) + HeadlessArrow - mHeight / 2);
        graphics->StrokeLine(GetX() - ArrowHeadSize, GetY() + (baseBoxHeight) + HeadlessArrow - mHeight / 2,
                             GetX() + ArrowHeadSize, GetY() + (baseBoxHeight) + HeadlessArrow - mHeight / 2);

    }
    else
    {
    graphics->StrokeLine(GetX(), GetY() + baseBoxHeight - mHeight / 2, GetX() - ArrowHeadSize,
                             GetY() + (baseBoxHeight) + ArrowHeadSize - mHeight / 2);
    graphics->StrokeLine(GetX(), GetY() + baseBoxHeight - mHeight / 2, GetX() + ArrowHeadSize,
                         GetY() + (baseBoxHeight) + ArrowHeadSize - mHeight / 2);
    graphics->StrokeLine(GetX() - ArrowHeadSize, GetY() + (baseBoxHeight) + ArrowHeadSize - mHeight / 2,
                             GetX() + ArrowHeadSize,
            GetY() + (baseBoxHeight) + ArrowHeadSize - mHeight / 2);
    graphics->StrokeLine(GetX(), GetY() + (baseBoxHeight) + ArrowHeadSize - mHeight / 2, GetX(),
                             GetY() + (baseBoxHeight) + ArrowSize - mHeight / 2);
    }

    // Now do everything for the second box
    attributeHit = 0;
    operationHit = 0;
    width = 0;
    graphics->GetTextExtent(mInheritance.GetDerived(), &wid, &hit);
    if (wid > width) { width = wid; }
    for (auto attributeContent : mSecondaryAttributes)
    {
        graphics->GetTextExtent(attributeContent.GetName(), &wid, &attributeHit);
        if (wid > width) { width = wid; }
    }
    for (auto operationContent : mSecondaryOperations)
    {
        graphics->GetTextExtent(operationContent.GetName(), &wid, &operationHit);
        if (wid > width) { width = wid; }
    }

    int baseBoxArrow = baseBoxHeight + ArrowSize;
    wid += Padding;

    graphics->GetTextExtent(mInheritance.GetDerived(), &wid, &nameHit);
    nameHit += Padding;
    graphics->DrawRectangle(GetX() - mWidthBottom / 2, GetY() - mHeight / 2 + baseBoxArrow, width + Padding, nameHit);
    graphics->DrawText(mInheritance.GetDerived(), GetX() + Padding + ((width - wid) / 2) - mWidthBottom / 2,
                           GetY() + Padding - mHeight / 2 + baseBoxArrow);

    attributeSize = mSecondaryAttributes.size();
    attributeHit += Padding;
    // Special case, no attributes and operations
    if (mSecondaryAttributes.empty() && mSecondaryOperations.empty())
    {
        attributeSize = 2;
    }
    graphics->DrawRectangle(GetX() - mWidthBottom / 2, (GetY() + nameHit - mHeight / 2) + baseBoxArrow,
                               width + Padding, attributeHit * attributeSize);

    i = 0;

    for (auto attributeContent : mSecondaryAttributes)
    {
        graphics->DrawText(attributeContent.GetName(), GetX() + Padding - mWidthBottom / 2, GetY() + nameHit + (attributeHit * i) - mHeight / 2 + baseBoxArrow);
        i++;
    }

    operationSize = mSecondaryOperations.size();
    operationHit += Padding;
    graphics->DrawRectangle(GetX() - mWidthBottom / 2, GetY() + nameHit + (attributeHit * attributeSize) - mHeight / 2
                               + baseBoxArrow, width + Padding, operationHit * operationSize);
    i = 0;
    for (auto operationContent : mSecondaryOperations)
    {
        graphics->DrawText(operationContent.GetName(), GetX() + Padding - mWidthBottom / 2,
                GetY() + nameHit + (attributeHit * attributeSize) + (operationHit * i) - mHeight / 2 + baseBoxArrow);
        i++;
    }

    mWidthBottom = width;

    mHeight = operationHit*operationSize + nameHit + attributeHit*attributeSize + baseBoxArrow;
}

/**
 * Initializes a basic UML dropdown (no inheritance)
 * @param game The game this drop down is a part of
 */
void DropDown::InitiateBasic(Game* game)
{
    // Get mData in order to load in UML texts
    UMLData data = GetGame()->GetData();

    // Initialize random seed
    srand(time(nullptr));


    auto random = GetGame()->GetRandom();
    std::uniform_int_distribution<> distribution(0, 1);
    mBad = distribution(random) == 1;

    int badContent = WaysToBeBad;

    if (mBad)
    {
        // Choose a random int value that will correspond to which UML content to be bad
        // 0 = Name, 1 = Attribute one, 2 = Attribute two, 3 = Operation one, 4 = Operation two
        std::uniform_int_distribution<> distributionBad(0, WaysToBeBad - 1);  //-1 from zero base

        badContent = distributionBad(random);
    }

    int index;
    std::vector<UMLValue> nameValues;
    if (badContent == NameIsBad)
    {
        nameValues = data.GetBadName();
    }
    else
    {
        nameValues = data.GetGoodName();
    }
    std::uniform_int_distribution<> distributionName(0, nameValues.size() - 1);  //-1 from zero base
    index = distributionName(random);
    mClassName = nameValues[index];

    // From now on the content may or may not exist, will use a 50% chance
    // Attributes
    bool exist;
    int oldGood = -1;
    exist = distribution(random) == 1;

    std::vector<UMLValue> attributeValues;
    if (badContent == AttributeOneIsBad)
    {
        attributeValues = data.GetBadAttribute();
    }
    else
    {
        attributeValues = data.GetGoodAttribute();
    }
    if (badContent == AttributeOneIsBad || exist)
    {
        std::uniform_int_distribution<> distributionAttributes(0, attributeValues.size() - 1);  //-1 from zero base

        index = distributionAttributes(random);
        mAttributes.push_back(attributeValues[index]);
        if (badContent != AttributeOneIsBad)
        {
            oldGood = index;
        }
    }

    exist = distribution(random) == 1;
    if (badContent == AttributeTwoIsbad)
    {
        attributeValues = data.GetBadAttribute();
    }
    else
    {
        attributeValues = data.GetGoodAttribute();
    }
    if (badContent == AttributeTwoIsbad || exist)
    {
        std::uniform_int_distribution<> distributionAttributes(0, attributeValues.size() - 1);  //-1 from zero base

        index = distributionAttributes(random);
        if (badContent != AttributeTwoIsbad)
        {
            while (index == oldGood)
            {
                index = distributionAttributes(random);
            }
        }
        mAttributes.push_back(attributeValues[index]);
    }

    // Operations
    oldGood = -1;
    exist = distribution(random) == 1;
    std::vector<UMLValue> operationValues;
    if (badContent == OperationOneIsBad)
    {
        operationValues = data.GetBadOperation();
    }
    else
    {
        operationValues = data.GetGoodOperation();
    }
    if (badContent == OperationOneIsBad || exist)
    {
        std::uniform_int_distribution<> distributionOperations(0, operationValues.size() - 1);  //-1 from zero base
        index = distributionOperations(random);
        mOperations.push_back(operationValues[index]);
        if (badContent != OperationOneIsBad)
        {
            oldGood = index;
        }
    }

    exist = distribution(random) == 1;
    if (badContent == OperationTwoIsBad)
    {
        operationValues = data.GetBadOperation();
    }
    else
    {
        operationValues = data.GetGoodOperation();
    }
    if (badContent == OperationTwoIsBad || exist)
    {
        std::uniform_int_distribution<> distributionOperations(0, operationValues.size() - 1);  //-1 from zero base
        index = distributionOperations(random);
        if (badContent != OperationTwoIsBad)
        {
            while (index == oldGood)
            {
                std::uniform_int_distribution<> distributionOperations(0, operationValues.size() - 1);  //-1 from zero base
                index = distributionOperations(random);
            }
        }
        mOperations.push_back(operationValues[index]);
    }
}

/**
 * Draw a Basic dropDown box
 * @param graphics the graphics context to draw on
 */
void DropDown::DrawBasic(wxGraphicsContext *graphics)
{
    /// Determine width and height of boxes by finding longest content text
    double wid, hit;
    double attributeHit = 0;
    double operationHit = 0;
    double width = 0;
    graphics->GetTextExtent(mClassName.GetName(), &wid, &hit);
    if (wid > width) { width = wid; }
    for (auto attributeContent : mAttributes)
    {
        graphics->GetTextExtent(attributeContent.GetName(), &wid, &attributeHit);
        if (wid > width) { width = wid; }
    }

    for (auto operationContent : mOperations)
    {
        graphics->GetTextExtent(operationContent.GetName(), &wid, &operationHit);
        if (wid > width) { width = wid; }
    }

    // Add some padding
    width += Padding;

    // Print out all the boxes and text
    double nameHit;
    graphics->GetTextExtent(mClassName.GetName(), &wid, &nameHit);

    // Special condition, completely empty box draw
    if (mClassName.GetAttribute() == L"Missing class name" && mAttributes.empty() && mOperations.empty())
    {
        width = ArrowSize;
    }
    nameHit += Padding;
    graphics->DrawRectangle(GetX() - mMaxWidth / 2, GetY() - mHeight / 2, width + Padding, nameHit);
    graphics->DrawText(mClassName.GetName(), GetX() + Padding + ((width - wid) / 2) - mMaxWidth / 2,
            GetY() + Padding - mHeight / 2);

    int attributeSize = mAttributes.size();
    attributeHit += Padding;

    // Special case, no attributes and operations
    if (mAttributes.empty() && mOperations.empty())
    {
        attributeSize = 2;
    }
    graphics->DrawRectangle(GetX() - mMaxWidth / 2, GetY() + nameHit - mHeight / 2, width + Padding,
                               attributeHit * attributeSize);
    int i = 0;
    for (auto attributeContent : mAttributes)
    {
        graphics->DrawText(attributeContent.GetName(), GetX() + Padding - mMaxWidth / 2,
                               GetY() + nameHit + (attributeHit * i) - mHeight / 2);
        i++;
    }

    int operationSize = mOperations.size();

    operationHit += Padding;

    graphics->DrawRectangle(GetX() - mMaxWidth / 2, GetY() + nameHit  + (attributeHit * attributeSize) - mHeight / 2,
                        width + Padding, operationHit * operationSize);

    i = 0;

    for (auto operationContent : mOperations)
    {
        graphics->DrawText(operationContent.GetName(), GetX() + Padding - mMaxWidth / 2,
                GetY() + nameHit + (attributeHit * attributeSize) + (operationHit * i) - mHeight / 2);
        i++;
    }
    mHeight = operationHit + nameHit + attributeHit;
    mMaxWidth = width;
}

/**
 * Test this item to see if it has been hit
 * @param x X location on the game to test in pixels
 * @param y Y location on the game to test in pixels
 * @return true if hit
 */
bool DropDown::HitTest(int x, int y)
{
    double larger = mMaxWidth;
    if (mWidthBottom > mMaxWidth)
    {
        larger = mWidthBottom;
    }
    if (GetX() - larger / 2 <= x && x <= GetX() + larger / 2)
    {
        if (GetY() - mHeight / 2 <= y && y <= GetY() + mHeight / 2)
        {
            return true;                // if the box is hit
        }
    }
    return false;                       // if the box is not hit
}

/**
 * Get all the content of a DropDown in a vector (in order from top to bottom)
 * @return all the UML values on the DropDown box
 */
std::vector<UMLValue> DropDown::GetContent()
{
    std::vector<UMLValue> contentVector;
    contentVector.push_back(mClassName);

    // adding attribute to the box
    for (const auto& attributeContent : mAttributes)
    {
        contentVector.push_back(attributeContent);
    }

    // adding the operations to the box
    for (const auto& operationContent : mOperations)
    {
        contentVector.push_back(operationContent);
    }

    // adding inheritance to the box
    contentVector.push_back(mInheritance);

    return contentVector;
}

/**
 * Behavior on removal to be overridden
 */
void DropDown::RemoveBehavior()
{
    auto game = GetGame();
    auto test = game->HitTest(GetX(), GetY());
    auto addRemovalItem = std::make_shared<Message>(game, test);
    addRemovalItem->SetLocation(GetX(), GetY());
    game -> Add(addRemovalItem);
    if (mBad)
    {
        game->IncrementCorrect();
    }
    else
    {
        game->IncrementUnfair();
    }

}

/**
 * Clears the DropDown from the game
 */
void DropDown::Clear()
{
    auto game = GetGame();
    auto test = game->HitTest(GetX(), GetY());
    auto addRemovalItem = std::make_shared<Message>(game, test);
    addRemovalItem->SetLocation(GetX(), GetY());

    // removing the drop down boxes for the variant
    game -> RemoveItem(test);
    game -> Add(addRemovalItem);
    game -> IncrementCorrect();
}

/**
 *  Tells if the Speed Boost has fallen through the bottom
 *  @return
 */
bool DropDown::OutOfBounds()
{
    auto game = GetGame();
    bool out = GetY() - mHeight / 2  > GetGame() -> Height;
    if (out)
    {
        if (mBad)
        {
            game->IncrementMissed();
        }
    }
    return out;
}