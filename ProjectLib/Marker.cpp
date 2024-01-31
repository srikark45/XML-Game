/**
 * @file Marker.cpp
 * @author Nathaniel
 */

#include "pch.h"

#include <string>
#include <memory>
#include <wx/graphics.h>
#include <cmath>

#include "Item.h"
#include "Marker.h"
#include "Game.h"

using namespace std;

/// Location of Harold's arm for Y in virtual pixels
const int LocationY = 800;

/// Speed of the marker in pixels a second
const double Boost = 2.0;

/// Base rotation of Marker in radians
const double BaseRotation = M_PI / 10;

/// Length to be from the center of Harold
const double VariantArmLength = 58.981;

/// Speed of the marker in pixels a second
const double VariantMarkerSpeed = 650;

/// Rotation Offset for variant
const double VariantOffSet = 3 * M_PI / 4;

/// Length to be from the center of Harold
const double ArmLength = 61.981;

/// Speed of the marker in pixels a second
const double MarkerSpeed = 600;

/// Rotation Offset for variant
const double OffSet = M_PI / 4;

/// SpeedFactor of marker speed boost
const double SpeedFactor = 7.5;

/**
 * Constructor for the marker
 *  @param game the game the marker is a part of
 *  @param filename the filename of the image for the marker
 *  @param variant whether this is a variant marker or not
 */
Marker::Marker(Game* game, const std::wstring &filename, const bool &variant) : Item(game)
{
    mItemImage = make_unique<wxImage>(filename , wxBITMAP_TYPE_ANY);
    mVariant = variant;

    // if we are in variant mode?
    if (mVariant)
    {
        mOffSet = VariantOffSet;
        mArmDistance = VariantArmLength;
        mSpeed = VariantMarkerSpeed;
    }
    else        // not in variant mode
    {
        mOffSet = OffSet;
        mArmDistance = ArmLength;
        mSpeed = MarkerSpeed;
    }
}

/**
 * Updates Marker for showing on the screen
 * @param elapsed time since last update
 */
void Marker::Update(double elapsed)
{

    Item::Update(elapsed);
    auto game = GetGame();
    mDuration += elapsed;

    // if not launches, the in harold's hand
    if (!mLaunched)
    {
        mRotation =  -BaseRotation + atan2(double(game->GetMouseY() - LocationY) , double(game -> GetMouseX()));
        SetLocation((cos(mRotation) * mArmDistance), (sin(mRotation) * mArmDistance) + LocationY);
    }

    if (mLaunched)
    {
        auto hitSomething = game->HitTest(GetX(), GetY());  // getting the hit place location
        if (hitSomething != nullptr)        // nullptr hit
        {
            hitSomething->SetRemove(true);
            mLaunched = false;
        }

        double xCoordinate = cos(mTrajectory) * mSpeed * elapsed;
        double yCoordinate = sin(mTrajectory) * mSpeed * elapsed;
        if (mBoosted)       // if in variant mode
        {
            xCoordinate = xCoordinate * Boost;
            yCoordinate = yCoordinate * Boost;
            if (mDuration > SpeedFactor)
            {
                mBoosted = !mBoosted;
                mDuration = 0;
            }
        }
        xCoordinate += GetX();
        yCoordinate += GetY();

        SetLocation(xCoordinate, yCoordinate);
        if (xCoordinate > game -> Width / 2 || xCoordinate < - game -> Width / 2  )
        {
            mLaunched = false;
        }
        if (yCoordinate > game -> Height || yCoordinate < 0)
        {
            mLaunched = false;
        }
        return;
    }

}

/**
 * Draw the view on a graphics context
 * @param graphics Graphics context to draw on
 */
void Marker::Draw(wxGraphicsContext *graphics)
{
    int itemWid = mItemImage->GetWidth();
    int itemHit = mItemImage->GetHeight();
    wxPoint center = wxPoint( int(GetX()) + itemWid / 2 + 1, int(GetY()) + itemHit / 2 + 1);
    auto tempImage = *make_unique<wxImage>(mItemImage->Rotate(-mRotation - mOffSet, center));
    mItemBitmap = graphics->CreateBitmapFromImage(tempImage);

    //
    // Draw a bitmap
    //

    graphics->DrawBitmap(mItemBitmap, GetX() - tempImage.GetWidth() / 2, GetY() - tempImage.GetHeight() / 2,
            tempImage.GetWidth(), tempImage.GetHeight());
}

/**
 * Launches the marker toward a location 
 * @param xCoordinate the x coordinate of the target location
 * @param yCoordinate the y coordinate of the target location
 */
void Marker::Launch()
{
    auto game = GetGame();

    // Just a test for now, will implement more later when doing hit test works for marker.

    if (!mLaunched)
    {
        Update(0);
        mTrajectory = atan2(double(game->GetMouseY() - GetY()) , double(game->GetMouseX() - GetX()));
        mLaunched = true;
    }
}

/**
 * Launches the marker toward a location
 */
void Marker::SpeedBoost()
{
    mBoosted = true;
    mDuration = 0;
}

