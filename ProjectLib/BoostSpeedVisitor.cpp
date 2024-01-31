/**
 * @file BoostSpeedVisitor.cpp
 * @author Zachary Troxell
 */

#include "pch.h"
#include "BoostSpeedVisitor.h"

/**
 *  Override for the visitor for marker
 *  @param marker the marker to be visited
 */
void BoostSpeedVisitor::VisitMarker(Marker* marker)
{
    marker->SpeedBoost();
}
