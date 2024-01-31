/**
 * @file SpeedBoost.cpp
 * @author Zachary Troxell
 */

#include "pch.h"
#include "SpeedBoost.h"

#include <memory>
#include <wx/graphics.h>

#include "Item.h"
#include "Game.h"
#include "Message.h"

using namespace std;

///Used for scaling down the image
const int scaling = 5;

/// Minimum speed in the x direction
const int MinSpeedX = -200;

///Maximum speed in the x direction
const int MaxSpeedX = 200;

/// Speed in the y direction
const int SpeedY = 100;

/// Random Distribution value
const int Distribution = 5;

/// SpeedBoost filename
const wstring SpeedBoostImage = L"images/speedboost.png";

/**
 * Constructor
 * @param game Game SpeedBoost is a member of
 */
SpeedBoost::SpeedBoost(Game* game) : Item(game)
{

    mItemImage = make_unique<wxImage>(SpeedBoostImage, wxBITMAP_TYPE_ANY);
    int itemWid = mItemImage->GetWidth();       // Get the width of the SpeedBoost
    int itemHit = mItemImage->GetHeight();      // Get the height of the SpeedBoost
    wxPoint center = wxPoint( int(GetX()) + itemWid / 2 + 1, int(GetY()) + itemHit / 2 + 1);
    mItemImage = make_unique<wxImage>(mItemImage->Rotate(-M_PI / 2, center));

    std::uniform_real_distribution<> distribution(MinSpeedX, MaxSpeedX);
    mSpeedX = distribution(game->GetRandom());      // Set the x speed

    mSpeedY = SpeedY;                               // Set the y speed
    mAccelerationX = 0;

    mItemBitmap = make_unique<wxBitmap>(*mItemImage);

}

/**
 * Updates SpeedBoost for showing on the screen
 * @param elapsed time since last update
 */
void SpeedBoost::Update(double elapsed)
{
    Item::Update(elapsed);

    if (mSpeedX < 0)            // if going in negative x direction
    {
        mSpeedX = mAccelerationX  * elapsed + mSpeedX;

        std::uniform_real_distribution<> distribution(0, Distribution);
        mAccelerationX = mAccelerationX + distribution(GetGame()->GetRandom());
    }
    else                        // if going in positive x direction
    {
        mSpeedX = mAccelerationX  * elapsed + mSpeedX;

        std::uniform_real_distribution<> distribution(-Distribution, 0);
        mAccelerationX = mAccelerationX + distribution(GetGame()->GetRandom());
    }
    SetLocation(GetX() + mSpeedX * elapsed, GetY() + mSpeedY * elapsed );

}

/**
 * Draw the view on a graphics context
 * @param graphics Graphics context to draw on
 */
void SpeedBoost::Draw(wxGraphicsContext *graphics)
{
    graphics->DrawBitmap(*mItemBitmap, GetX() - mItemBitmap->GetWidth() / scaling / 2,
            GetY() - mItemBitmap -> GetHeight() / scaling / 2,
            mItemBitmap->GetWidth() / scaling, mItemBitmap->GetHeight() / scaling);
}

/**
 * Test this item to see if it has been hit
 * @param x X location on the game to test in pixels
 * @param y Y location on the game to test in pixels
 * @return true if hit
 */
bool SpeedBoost::HitTest(int x, int y)
{
    double wid = mItemBitmap -> GetWidth();
    double hit = mItemBitmap -> GetHeight();

    // Make x and y relative to the top-left corner of the bitmap image
    // Subtracting the center makes x, y relative to the image center
    // Adding half the size makes x, y relative to theimage top corner
    double testX = x - GetX() + wid / scaling / 2;
    double testY = y - GetY() + hit / scaling  / 2;

    // Test to see if x, y are in the image
    if (testX < 0 || testY < 0 || testX >= wid / scaling || testY >= hit / scaling)
    {
        // We are outside the image
        return false;
    }

    // Test to see if x, y are in the drawn part of the image
    // If the location is transparent, we are not in the drawn
    // part of the image
    return !mItemImage -> IsTransparent((int)testX * scaling, (int)testY * scaling);
}

/**
 * Behavior on removal to be overridden
 */
void SpeedBoost::RemoveBehavior()
{
    auto game = GetGame();
    game -> BoostMarkerSpeed();
    auto addRemovalItem = make_shared<Message>(game, game->HitTest(GetX(), GetY()));
    addRemovalItem->SetLocation(GetX(), GetY());
    game ->Add(addRemovalItem);
}

/**
 * Set the item location
 * @param x X location in pixels
 * @param y Y location in pixels
 */
void SpeedBoost::SetLocation(double x, double y)
{
    Item::SetLocation(x, y);

    if (GetY() > GetGame() -> Height)
    {
        mOutOfBounds = true;
    }
}
