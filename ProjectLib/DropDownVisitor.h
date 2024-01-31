/**
 * @file DropDownVisitor.h
 * @author Ian Hay
 * Description of a DropDownVisitor for clearing
 */

#ifndef PROJECT1_DROPDOWNVISITOR_H
#define PROJECT1_DROPDOWNVISITOR_H



#include "Marker.h"
#include "DropDown.h"
/// Visitor for clearing DropDown boxes
class DropDownVisitor : public ItemVisitor
{
private:


public:
    void VisitDropDown(DropDown* dropDown) override;

};

#endif //PROJECT1_DROPDOWNVISITOR_H
