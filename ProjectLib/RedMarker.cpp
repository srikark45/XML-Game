/**
 * @file RedMarker.cpp
 * @author Rajaditya Shrikishan Bajaj
 */
#include "pch.h"

#include <string>

#include "RedMarker.h"
#include "Game.h"
#include "Item.h"

using namespace std;

///File Path for the red pen image
const wstring RedPenImage = L"images/redpen.png";

/// is variant?
bool isVariant = false;

/**
 * Constructor for the red marker
 * @param game the game the marker is a part of
 */
RedMarker::RedMarker(Game *game) :Marker(game, RedPenImage, isVariant)
{

}