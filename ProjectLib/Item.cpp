/**
 * @file Item.cpp
 * @author Team Grady Wins (Zachary Troxell)
 */

#include "pch.h"

#include <wx/graphics.h>

#include "Item.h"
#include "Game.h"

using namespace std;

/**
 * Destructor
 */
Item::~Item()
{
}

/**
 * Constructor
 * @param game The game this item is a member of
 */
Item::Item(Game *game) : mGame(game)
{
}


/**
 * Draw the item
 * @param graphics The graphics context to draw on
 */
void Item::Draw(wxGraphicsContext *graphics)
{

}


