/**
 * @file GreenMarker.cpp
 * @author Rajaditya Bajaj
 */

#include "pch.h"

#include <string>
#include <memory>
#include <wx/graphics.h>
#include <cmath>

#include "Item.h"
#include "GreenMarker.h"
#include "Game.h"

using namespace std;

/// Green Marker filename
const wstring GreenPenImage = L"images/greenpen.png";

/// is variant?
bool isGreenVariant = true;

/**
 * Constructor for the Green marker
 * @param game the game the marker is a part of
 */
GreenMarker::GreenMarker(Game *game) : Marker(game, GreenPenImage, isGreenVariant)
{

}