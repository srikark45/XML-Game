/**
 * @file LaunchVisitor.cpp
 * @author Zachary Troxell
 */

#include "pch.h"

#include "LaunchVisitor.h"

/**
 * Override for the visitor for marker
 * @param marker the marker to be visited
 */
void LaunchVisitor::VisitMarker(Marker* marker)
{
    marker->Launch();
}
