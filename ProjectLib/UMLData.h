/**
 * @file UMLData.h
 * @author Team Grady Twins (Rajaditya Bajaj)
 *
 * This class stores the UML parsing in vectors in form of good
 * or bad UML with its attribute.
 */

#ifndef PROJECT1_UMLDATA_H
#define PROJECT1_UMLDATA_H

#include "UMLValue.h"
#include <vector>
#include <wx/string.h>

/**
 * Class storing UML Parsing.
 */
class UMLData
{
public:
    void SetName(bool isBad, const UMLValue& nameValue);

    void SetAttribute(bool isBad, const UMLValue& attributeValue);

    void SetOperation(bool isBad, const UMLValue& operationValue);

    void SetInheritance(bool isBad, const UMLValue& inheritValue);

    /**
     * this function gets good name vector
     * @return good name vector
     */
    std::vector<UMLValue> GetGoodName() {return mGoodNames;}

    /**
     *  this function get good attribute vector
     * @return good attribute vector
     */
    std::vector<UMLValue> GetGoodAttribute() {return mGoodAttributes;}

    /**
     * this function returns good operation vector
     * @return good operation vector
     */
    std::vector<UMLValue> GetGoodOperation() {return mGoodOperations;}

    /**
     * This function returns good inheritance vector
     * @return good inheritance vector
     */
    std::vector<UMLValue> GetGoodInheritance() {return mGoodInheritance;}

    /**
    * This function returns bad name vector
    * @return bad name vector
    */
    std::vector<UMLValue> GetBadName() {return mBadNames;}

    /**
     * This function returns the bad attribute vector
     * @return bad attribute vector
     */
    std::vector<UMLValue> GetBadAttribute() {return mBadAttributes;}

    /**
     * This function returns the bad operation vector
     * @return bad operation vector
     */
    std::vector<UMLValue> GetBadOperation() {return mBadOperations;}

    /**
     * This function returns the bad inheritance vector
     * @return bad inheritance vector
     */
    std::vector<UMLValue> GetBadInheritance() {return mBadInheritance;}

private:
    /// A list of good class names
    std::vector<UMLValue> mGoodNames;

    /// A list of bad class names
    std::vector<UMLValue> mBadNames;

    /// A list of good Uml attributes
    std::vector<UMLValue> mGoodAttributes;

    /// A list of bad Uml attributes
    std::vector<UMLValue> mBadAttributes;

    /// A list of good Uml Operations
    std::vector<UMLValue> mGoodOperations;

    /// A list of bad Uml Operations
    std::vector<UMLValue> mBadOperations;

    /// A list of good Inheritance info
    std::vector<UMLValue> mGoodInheritance;

    /// A list of bad Uml Inheritance info
    std::vector<UMLValue> mBadInheritance;

};

#endif //PROJECT1_UMLDATA_H
