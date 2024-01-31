/**
 * @file DropDownVisitor.cpp
 * @author Ian Hay
 */
#include "pch.h"

#include "DropDownVisitor.h"

/**
 * Override for the visitor for dropdown
 * @param drop the DropDown to be visited
 */
void DropDownVisitor::VisitDropDown(DropDown* drop)
{
    drop->Clear();
}