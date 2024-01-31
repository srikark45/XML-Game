/**
 * @file Harold.cpp
 * @author Team Grady Twins ( Raj and Zach )
 */

#include "pch.h"

#include <memory>
#include <wx/graphics.h>
#include <math.h>

#include "Item.h"
#include "Harold.h"
#include "Game.h"


/// Location of Image's arm for Y in virtual pixels
const int LocationY = 800;

/// Base rotation of Harold in radians
const double BaseRotation = M_PI / 4;

using namespace std;

/**
 * Constructor
 * @param game Game harold is a member of
 * @param filename the filename for the image
 */
Harold::Harold(Game* game, const std::wstring &filename) : Item(game)
{
    mItemImage = make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);

}

/**
 * Updates Harold for showing on the screen
 * @param elapsed time since last update
 */
void Harold::Update(double elapsed)
{
    Item::Update(elapsed);

    auto game = GetGame();

    // base rotation
    mRotation = -BaseRotation - atan2(double(game->GetMouseY() - LocationY) , double(game->GetMouseX()));

}

/**
 * Draw the view on a graphics context
 * @param graphics Graphics context to draw on
 */
void Harold::Draw(wxGraphicsContext *graphics)
{
    int itemWid = mItemImage->GetWidth();
    int itemHit = mItemImage->GetHeight();
    wxPoint center = wxPoint( int(GetX()) + itemWid / 2 + 1, int(GetY()) + itemHit / 2 + 1);
    auto tempImage = *make_unique<wxImage>(mItemImage->Rotate(mRotation, center));
    mItemBitmap = graphics->CreateBitmapFromImage(tempImage);

    //
    // Draw a bitmap
    //

    graphics->DrawBitmap(mItemBitmap, GetX() - tempImage.GetWidth() / 2, GetY()- tempImage.GetHeight() / 2,
            tempImage.GetWidth(), tempImage.GetHeight());
}
