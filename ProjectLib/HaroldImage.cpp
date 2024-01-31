/**
 * @file HaroldImage.cpp
 * @author Rajaditya Shrikishan Bajaj
 */
#include "pch.h"

#include <string>

#include "HaroldImage.h"
#include "Game.h"

using namespace std;

/// Harold filename
const wstring haroldImage = L"images/harold.png";

/**
 * Creates the basic harold
 * @param game the game Harold is a part of
 */
HaroldImage::HaroldImage(Game* game) : Harold(game, haroldImage)
{

}