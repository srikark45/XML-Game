/**
 * @file MessageGettingVistior.cpp
 * @author Zachary Troxell
 */

#include "pch.h"

#include "MessageGettingVistior.h"
#include "DropDown.h"

/**
 * Override for the visitor for DropDown
 * @param dropDown the dropdown to be visited
 */
void MessageGettingVistior::VisitDropDown(DropDown* dropDown)
{
    auto potentialMessages = dropDown->GetContent();
    auto begin = potentialMessages.begin();
    auto end = potentialMessages.end();
    // Go over all of the attributes to see if any are for bad UML
    for ( ; begin != end; ++begin)
    {
        if (begin->GetAttribute() != "")
        {
            mMessage = begin->GetAttribute();
        }
    }
    if (mMessage == "")
    {
        mMessage = "Unfair!";
    }
}

/**
 * Override for the visitor for SpeedBoost
 * @param speedBoost the speedBoost to be visited
 */
void MessageGettingVistior::VisitSpeedBoost(SpeedBoost* speedBoost)
{
    mMessage = "BOOST";
}

/**
 * Override for the visitor for ClearScreen
 * @param clearScreen the speedBoost to be visited
 */
void MessageGettingVistior::VisitClearScreen(ClearScreenPU *clearScreen)
{
    mMessage = "CLEAR";
}