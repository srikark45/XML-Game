/**
 * @file LaunchVisitor.h
 * @author Zachary Troxell
 *
 * Visitor for launching the marker
 */

#ifndef PROJECT1_LAUNCHVISITOR_H
#define PROJECT1_LAUNCHVISITOR_H

#include "ItemVisitor.h"
#include "Marker.h"

/**
 * Visiot for launching the marker
 */
class LaunchVisitor : public ItemVisitor
{
private:
    /// The x Coordinate to move marker towards
    double mXCoordinate;

    /// The y Coordinate to move marker towards
    double mYCoordinate;

public:

    void VisitMarker(Marker* marker) override;

    /**
     * Set the location of the target
     * @param x x location of the target
     * @param y y location of the target
     */
    void SetTargetLocation(double x, double y) { mXCoordinate = x; mYCoordinate = y; }

};

#endif //PROJECT1_LAUNCHVISITOR_H
