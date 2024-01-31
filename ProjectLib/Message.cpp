/**
 * @file Message.cpp
 * @author Zachary Troxell
 */

#include "pch.h"

#include "Message.h"
#include "Game.h"
#include "MessageGettingVistior.h"

/// Constant for full saturation for brushes
const int FullSaturation = 255;

/// Font size for messages
const int FontSize = 30;

/// Delay before deleteing the message
const int Delay = 50;

/**
 * Constructor
 * @param game the game the message is a part of
 * @param item the item that the message is for
 */
Message::Message(Game* game, std::shared_ptr<Item> item) : Item(game)
{
    mItemWithMessage = item;
    MessageGettingVistior visitor;
    item->Accept(&visitor);
    mMessage = visitor.GetMessage();
    mUpdateCycles = 0;
}

/**
 *Updates Message for showing on the screen
 * @param elapsed time since last update
 */
void Message::Update(double elapsed)
{
    Item::Update(elapsed);
    if (mUpdateCycles++ > Delay)
    {
        mRemoval = true;
        auto game = GetGame();
        auto sharedVersionOfThis = game->HitTest(GetX(), GetY());   // checking if it has been hit
        sharedVersionOfThis->SetRemove(true);   // if the message has been hit
    }

}

/**
 * Draw the view on a graphics context
 * @param graphics Graphics context to draw on
 */
void Message::Draw(wxGraphicsContext* graphics)
{
    mItemWithMessage->Draw(graphics);
    wxBrush brush(wxColour(0, 0, FullSaturation));
    graphics->SetBrush(brush);
    auto myFont = wxFont();
    myFont.SetPointSize(FontSize);

    if (mMessage == "Unfair!")
    {
        graphics->SetFont(myFont, *wxRED);

    }
    else
    {
        graphics->SetFont(myFont, *wxGREEN);
    }

    double width = 0;
    double height = 0;
    graphics->GetTextExtent(mMessage, &width, &height);

    graphics->DrawText(mMessage, GetX() - width / 2, GetY() - height / 2);
}

