/**
 * @file UMLData.cpp
 * @author Team Grady Wins (Rajaditya Bajaj)
 */

#include "pch.h"

#include <vector>
#include <wx/string.h>
#include <wx/xml/xml.h>

#include "UMLValue.h"
#include "UMLData.h"

using namespace std;

/**
 * Adds the name value to the vector
 * @param isBad if the attribute is bad
 * @param nameValue the name of the input
 */
void UMLData::SetName(bool isBad, const UMLValue& nameValue)
{
    // If bad name
    if (isBad)
    {
        mBadNames.push_back(nameValue);
    }
    else        // if good name
    {
        mGoodNames.push_back(nameValue);
    }
}

/**
 * This function sets the attribute for the input.
 * @param isBad if the attribute is bad or not.
 * @param attributeValue inputs the attribute
 */
void UMLData::SetAttribute(bool isBad, const UMLValue& attributeValue)
{
    if (isBad)  // if bad attribute
    {
        mBadAttributes.push_back(attributeValue);
    }
    else
    {
        mGoodAttributes.push_back(attributeValue);
    }
}

/**
 * This function pushes back the operation in the given vector.
 * @param isBad if the operation is bad
 * @param operationValue the name of the operation
 */
void UMLData::SetOperation(bool isBad, const UMLValue& operationValue)
{
    if (isBad)  // if bad operation
    {
        mBadOperations.push_back(operationValue);
    }
    else
    {
        mGoodOperations.push_back(operationValue);
    }
}

/**
 * This function pushes back the inheritance in the given vector.
 * @param isBad if the inheritance is good or bad.
 * @param inheritValue the name of the inherit
 */
void UMLData::SetInheritance(bool isBad, const UMLValue& inheritValue)
{
    if (isBad)  // if bad inheritance
    {
        mBadInheritance.push_back(inheritValue);
    }
    else
    {
        mGoodInheritance.push_back(inheritValue);
    }
}
