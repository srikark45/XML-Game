/**
 * @file Bob.cpp
 * @author Rajaditya Shrikishan BAjaj
 */
#include "pch.h"

#include <string>

#include "Bob.h"
#include "Game.h"

using namespace std;

/// Harold filename
const wstring bobImage = L"images/bob.png";

Bob::Bob(Game* game) : Harold(game, bobImage)
{

}
