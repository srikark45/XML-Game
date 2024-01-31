/**
 * @file UMLValue.h
 * @author Team Grady Wins (Rajaditya Bajaj)
 *
 * This class is for storing the different values we have in
 * node.
 */

#ifndef PROJECT1_UMLVALUE_H
#define PROJECT1_UMLVALUE_H

#include <vector>
#include <wx/string.h>

/**
 * Class for different values
 */
class UMLValue
{
public:

    /**
     * Updates the value of the string
     * @param str the input string
     */
    void SetName(const wxString& str) { mName = str; }

    /**
     * Updates the value of the attribut
     * @param attribute the input attribute
     */
    void SetAttribute(const wxString& attribute) {mAttribute = attribute;}

   /**
    * Updates the boolean if it bad or not.
    * @param bad the input boolean
    */
    void SetBad(bool bad) { mBad = bad; }

    /**
     * Returns the name of value.
     * @return the value
     */
    wxString GetName() { return mName; }

    /**
     * Returns the attribute
     * @return attribute
     */
    wxString GetAttribute() { return mAttribute; }

    /**
     * Returns the boolean
     * @return boolean
     */
    bool IsBad() const { return mBad; }

    /**
    * Sets the base for inheritance
    * @param str the base
    */
    void SetBase(const wxString& str) { mBase = str; }

    /**
     * Sets the derived for inheritance
     * @param str the derived
     */
    void SetDerived(const wxString& str) { mDerived = str; }

    /**
     * Sets the direction for inheritance
     * @param str the direction
     */
    void SetDirection(const wxString& str) { mDirection = str; }

    /**
    * Returns the base of the inheritance
    * @return the inheritance
    */
    wxString GetBase() { return mBase; }

    /**
     * Return the derived of the inheritance
     * @return the derived
     */
    wxString GetDerived() { return mDerived; }

    /**
     * Return the direction of the inheritance
     * @return the direction
     */
    wxString GetDirection() { return mDirection; }

private:
    /// represents if this is an incorrect value
    bool mBad;

    /// represents the attribute
    wxString mAttribute = L"";

    /// a string representing useful Uml name
    wxString mName = L"";

    /// Base class for inheritance scenario
    wxString mBase = L"";

    /// Derived Class for inheritance scenario
    wxString mDerived = L"";

    /// Direction of inheritance
    wxString mDirection = L"up";
};

#endif //PROJECT1_UMLVALUE_H
