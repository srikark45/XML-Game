/**
 * @file BoostSpeedVisitor.h
 * @author Zachary Troxell
 *
 * visitor for boosting marker speed
 */

#ifndef PROJECT1_BOOSTSPEEDVISITOR_H
#define PROJECT1_BOOSTSPEEDVISITOR_H

#include "ItemVisitor.h"
#include "Marker.h"

/**
 * Visitor for launching the marker
 */
class BoostSpeedVisitor : public ItemVisitor
{
public:

    void VisitMarker(Marker* marker) override;

};

#endif //PROJECT1_BOOSTSPEEDVISITOR_H
