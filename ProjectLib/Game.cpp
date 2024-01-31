/**
 * @file Game.cpp
 * @author Team Grady Twins (Zachary Troxell)
 */

#include "pch.h"

#include <vector>
#include <wx/string.h>
#include <wx/xml/xml.h>
#include <wx/graphics.h>

#include "Game.h"
#include "Item.h"
#include "Harold.h"
#include "Marker.h"
#include "LaunchVisitor.h"
#include "BoostSpeedVisitor.h"
#include "DropDown.h"
#include "GreenMarker.h"
#include "RedMarker.h"
#include "HaroldImage.h"
#include "Bob.h"
#include "UMLValue.h"
#include "SpeedBoost.h"
#include "ClearScreenPU.h"
#include "DropDownVisitor.h"
#include "Scoreboard.h"

using namespace std;

/// The y coordinate of Harold
const int HaroldYCoordinate = 800;

/// X coordinate for Marker
const int MarkerXCoordinate = 28;

/// Y coordinate for Marker
const int MarkerYCoordinate = 745;

/// File to load in XML UML data from
const wxString FileXML = L"data/uml.xml";

/// After this time add an item
const int AddItem = 2;

///Drop coordinate
const int DropCoordinateY = -200;

/**
 * Draw the game area
 * @param graphics The graphics context to draw on
 * @param width Width of the client window
 * @param height Height of the client window
 */
void Game::OnDraw(wxGraphicsContext *graphics, int width, int height)
{

    //
    // Automatic Scaling
    //
    auto scaleX = double(width) / double(Width);
    auto scaleY = double(height) / double(Height);
    mScale = min(scaleX, scaleY);

    mXOffset = width / 2;
    mYOffset = 0;
    if (height > Height * mScale)
    {
        mYOffset = (float)((height - Height * mScale) / 2);
    }

    graphics->PushState();

    graphics->Translate(mXOffset, mYOffset);
    graphics->Scale(mScale, mScale);

    //
    // Draw in virtual pixels on the graphics context
    //
    wxBrush background(*wxWHITE);
    graphics->SetBrush(background);

    graphics->DrawRectangle(-Width / 2 , 0, Width, Height);
    graphics->Clip(-Width / 2 , 0, Width, Height);

    // If we are in variant mode
    if ((mSpeedBoostCounter > 24) && mVariant)
    {
        auto speedBooster = make_shared<SpeedBoost>(this);
        Game::Add(speedBooster);
        mSpeedBoostCounter = 0;
    }

    // If we are in variant mode
    if ((mClearScreenCounter > 32) && mVariant)
    {
        auto clearScreenPU = make_shared<ClearScreenPU>(this);
        Game::Add(clearScreenPU);
        mClearScreenCounter = 0;
    }

    // Adds the dropdown to the screen
    if (mInterval > AddItem)
    {
        auto dropdown = make_shared<DropDown>(this);
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 eng(rd()); // seed the generator

        std::uniform_int_distribution<> distribution(-GetOffsetX(), GetOffsetX()); // define the range

        dropdown->SetLocation( distribution(eng), DropCoordinateY);
        Game::Add(dropdown);
        mInterval = 0;
    }

    // Draws the item in the game
    for (const auto& item : mItems)
    {
        item->Draw(graphics);
    }

    mScoreboard->Draw(graphics);

    graphics->PopState();

}

/**
 * Game Constructor
 */
Game::Game()
{
    // Seed the random number generator
    std::random_device rd;
    mRandom.seed(rd());

    // adds the marker
    auto marker = make_shared<RedMarker>(this);
    marker->SetLocation(MarkerXCoordinate, MarkerYCoordinate);
    Game::Add(marker);

    // adds the harold
    auto harold = make_shared<HaroldImage>(this);
    harold->SetLocation(0, HaroldYCoordinate);
    Game::Add(harold);

    // Interval of the game
    mInterval = AddItem;

    // adds the scoreboard to the game
    mScoreboard = make_shared<Scoreboard>(this);

    // Load in UML
    Game::Load(FileXML);
}


/**
 * Add an item to the Game
 * @param item New item to add
 */
void Game::Add(const std::shared_ptr<Item>& item)
{
    mItems.push_back(item);
}


/**
 * Test an x,y click location to see if a non pen item is hit
 * on some item in the game.
 * @param x x X location in pixels
 * @param y y Y location in pixels
 * @return Pointer to item we hit on or nullptr if none.
 */

std::shared_ptr<Item> Game::HitTest(int x, int y)
{
    for (auto i = mItems.rbegin(); i != mItems.rend();  i++)
    {
        if ((*i) -> HitTest(x, y))      // if it has been hit?
        {
            if (*i != nullptr)
            {
                return *i;
            }
        }
    }

    return  nullptr;
}

/**
 * Removes items from the game that had a collision
 */
void Game::RemoveItems()
{
    for (auto j = mItems.rbegin(); j!=mItems.rend(); j++)
    {
        if (j->get()->GetRemove())              // if it has to be removed?
        {
            auto temp = *j;                     // making a temporary variable
            temp.get()->RemoveBehavior();
            auto loc = find(begin(mItems), end(mItems), temp);
            if (loc!=end(mItems))
            {
                mItems.erase(loc);
                return;
            }
        }
    }
}

/**
 * Remove a single item from the game
 * @param item the item to be removed
 */
void Game::RemoveItem(std::shared_ptr<Item>& item)
{
    auto loc = find(begin(mItems), end(mItems), item);
    mItems.erase(loc);
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Game::Update(double elapsed)
{
    mScoreboard->Update(elapsed);
    for (const auto& item : mItems)
    {
        item->Update(elapsed);
    }
    OutOfBoundsItem();
    RemoveItems();
}

/**
 * Launches marker
 * @param xCoordinate the x location of the target
 * @param yCoordinate the y location of the target
 */
void Game::Launch(double xCoordinate, double yCoordinate)
{
    LaunchVisitor visitor;
    visitor.SetTargetLocation(xCoordinate, yCoordinate);
    Accept(&visitor);
}

/**
 * Accept a visitor for the collection
 * @param visitor The visitor for the collection
 */
void Game::Accept(ItemVisitor* visitor)
{
    for (auto item : mItems)
    {
        item->Accept(visitor);
    }
}

/**
 * Loads the uml.xml for the game
 * @param filename the name of the file
 */
void Game::Load(const wxString& filename)
{
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load the uml.xml file");
        return;
    }

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    //
    // Traverse the children of the root
    // node of the XML document in memory!!!!
    //
    auto child = root->GetChildren();
    for( ; child; child=child->GetNext())
    {
        const auto& name = child->GetName();

        // Traversing the class
        if (name == L"class")
        {
            auto childClass = child->GetChildren();
            for (; childClass; childClass = childClass->GetNext())
            {
                const auto& childName = childClass->GetName();
                // Traversing the name of the class
                if (childName == L"name")
                {
                    UMLValue nameValue;
                    bool isBad = !childClass->GetAttribute(L"bad").empty(); // is bad class?
                    nameValue.SetName(childClass->GetNodeContent());
                    nameValue.SetBad(isBad);
                    nameValue.SetAttribute(childClass->GetAttribute(L"bad"));
                    mData.SetName(isBad, nameValue);
                }
                // traversing the attributes
                else if (childName == L"attribute")
                {
                    UMLValue attributeValue;
                    bool isBad = !childClass->GetAttribute(L"bad").empty(); // is bad attribute?
                    attributeValue.SetName(childClass->GetNodeContent());
                    attributeValue.SetBad(isBad);
                    attributeValue.SetAttribute(childClass->GetAttribute(L"bad"));
                    mData.SetAttribute(isBad, attributeValue);
                }
                // traversing the operations
                else if (childName == L"operation")
                {
                    UMLValue operationValue;
                    bool isBad = !childClass->GetAttribute(L"bad").empty(); // is bad operation
                    operationValue.SetName(childClass->GetNodeContent());
                    operationValue.SetBad(isBad);
                    operationValue.SetAttribute(childClass->GetAttribute(L"bad"));
                    mData.SetOperation(isBad, operationValue);
                }
            }

        }
        // traversing the inheritance
        else if (name == L"inheritance")
        {
            // reads necessary data into InheritData (bases, derived, bad)
            auto childInherit = child->GetChildren();
            for (; childInherit; childInherit = childInherit->GetNext())
            {
                UMLValue inheritValue;
                bool isBad = !childInherit->GetAttribute(L"bad").empty();   // is bad inheritance?
                inheritValue.SetBad(isBad);
                inheritValue.SetAttribute(childInherit->GetAttribute(L"bad"));
                inheritValue.SetBase(childInherit->GetAttribute(L"base"));
                inheritValue.SetDerived(childInherit->GetAttribute(L"derived"));
                bool direction = !childInherit->GetAttribute(L"direction").empty(); // direction of the arrow
                if (direction)
                {
                    inheritValue.SetDirection(childInherit->GetAttribute(L"direction"));
                }
                mData.SetInheritance(isBad, inheritValue);
            }
        }
    }
}

/**
 * Sets the known location for mouse
 * @param x x location of the mouse
 * @param y the y location of the mouse
 */
void Game::SetMouseLocation(int x, int y)
{
    mMouseX = (x - mXOffset) / mScale;
    mMouseY = (y - mYOffset) / mScale;
}

/**
 * Removes out of bounds items
 */
void Game::OutOfBoundsItem()
{
    for (auto i = mItems.rbegin(); i!=mItems.rend(); i++)
    {
        if ((*i)->OutOfBounds())
        {
            auto loc = find(begin(mItems), end(mItems), *i);

            if (loc!=end(mItems))
            {
                mItems.erase(loc);
                break;
            }
        }
    }
}

/**
 * Applies a speed boost
 */
void Game::BoostMarkerSpeed()
{
    BoostSpeedVisitor visitor;
    Accept(&visitor);
}

/**
 * Clear the game of all UML Boxes
 */
void Game::ClearUMLBoxes()
{
    for (auto item : mItems)
    {
        DropDownVisitor visitor;
        Accept(&visitor);
    }

}

/**
 * Set the Game to variant or standard mode
 * @param variant whether entering variant or standard
 */
void Game::SetVariant(bool variant)
{
    mVariant = variant;
    // if we are in variant state
    if (mVariant)
    {
        mItems.clear();

        auto bob = make_shared<Bob>(this);  // adding bob instead of harold
        bob->SetLocation(0, HaroldYCoordinate);
        auto add = mItems.insert(mItems.begin(), bob);

        auto marker = make_shared<GreenMarker>(this);   // adding green marker instead of red marker
        marker->SetLocation(MarkerXCoordinate, MarkerYCoordinate);
        auto addMarker = mItems.insert(mItems.begin(), marker);

        auto clearScreenPU = make_shared<ClearScreenPU>(this);  // adding the ClearScreenPU
        Game::Add(clearScreenPU);

        auto speedBooster = make_shared<SpeedBoost>(this);      // adding the SpeedBoost
        Game::Add(speedBooster);
    }

    else
    {
        mItems.clear();

        auto harold = make_shared<HaroldImage>(this);   // adding the normal harold
        harold->SetLocation(0, HaroldYCoordinate);
        auto addHarold = mItems.insert(mItems.begin(), harold);

        auto marker = make_shared<RedMarker>(this);     // adding the red marker
        marker->SetLocation(MarkerXCoordinate, MarkerYCoordinate);
        auto it = mItems.insert(mItems.begin(), marker);
    }
}

/**
  * Sets the elapsed time
  * @param elapsed the time elapsed
  */
void Game::SetElapsed(double elapsed)
{
    mElapsed += elapsed;
    mSpeedBoostCounter += elapsed;  // for making new variant
    mClearScreenCounter += elapsed;
    mInterval += elapsed;           // for dropdown boxes
}

/**
 * Increment the scoreboard correct value
 */
void Game::IncrementCorrect()
{
    mScoreboard->IncCorrect();
}

/**
 * Increment the scoreboard Unfair value
 */
void Game::IncrementUnfair()
{
    mScoreboard->IncUnfair();
}

/**
 * Increment the scoreboard missed value
 */
void Game::IncrementMissed()
{
    mScoreboard->IncMissed();
}