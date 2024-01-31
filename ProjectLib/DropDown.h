/**
 * @file DropDown.h
 * @author Team Grady Wins (Srikar Kante)
 *
 * Class that adds or draws the UML on the screen
 * and make them move.
 */

#ifndef PROJECT1_DROPDOWN_H
#define PROJECT1_DROPDOWN_H

#include <vector>
#include "Item.h"
#include "UMLValue.h"

/**
 * Class that adds the dropdown on the screen.
 */
class DropDown : public Item
{
private:
    ///Speed used to move down the screen
    double mSpeedY;

    ///Speed used ot move across the screen
    double mSpeedX;

    ///Width of the bottom box
    double mWidthBottom = 0;

    ///Width of the outer most box
    double mMaxWidth = 0;

    /// Height of the outer most box
    double mHeight = 0;

    ///Is this dropdown bad or good?
    bool mBad{};

    ///Is this dropdown inheritance or basic?
    bool mBasic;

    ///UML Value vectors / variables;
    UMLValue mClassName;

    ///UML Attributes
    std::vector<UMLValue> mAttributes;

    ///UML Attrubutes for inherited
    std::vector<UMLValue> mSecondaryAttributes;

    ///UML Operations
    std::vector<UMLValue> mOperations;

    ///UML operations for inherited
    std::vector<UMLValue> mSecondaryOperations;

    ///UML Inheritance
    UMLValue mInheritance;

public:
    /// Default constructor (disabled)
    DropDown() = delete;

    /// Assignment operator
    void operator=(const DropDown &) = delete;

    /// Copy constructor (disabled)
    DropDown(const DropDown &) = delete;

    /// Constructor
    DropDown(Game* game);

    void InitiateBasic(Game* game);

    void Update(double elapsed) override;

    /**
    * Draw the item
    * @param graphics The graphics context to draw on
    */
    void Draw(wxGraphicsContext *graphics) override;

    void DrawBasic(wxGraphicsContext *graphics);

    /**
     * Initiate an inherited dropdown
     * @param game the game the dropdown is a part of
     */
    void InitiateInheritance(Game *game);
    /**
     * draw an inherited dropdown
     * @param graphics The grahpicscontext to draw on
     */
    void DrawInheritance(wxGraphicsContext *graphics);

    bool HitTest(int x, int y) override;

    std::vector<UMLValue> GetContent();

    /// Get the badness of a DropDown
    /// @return true if a bad UML false otherwise
    bool GetBadness() { return mBad; }

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    virtual void Accept(ItemVisitor* visitor) override { visitor->VisitDropDown(this); }

    void RemoveBehavior() override;

    void Clear();

    bool OutOfBounds() override;
};

#endif //PROJECT1_DROPDOWN_H
