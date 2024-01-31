/**
 * @file Harold.h
 * @author Team Grady Wins (Srikar Kante)
 *
 * Base class describing the person
 */

#ifndef PROJECT1_HAROLD_H
#define PROJECT1_HAROLD_H

#include <wx/graphics.h>

#include "Item.h"

/**
 * Base class describing the person
 */
class Harold : public Item
{
private:
    /// The item image
    std::shared_ptr<wxImage> mItemImage;

    /// The item bitmap
    wxGraphicsBitmap mItemBitmap;

    /// Current rotation (in radians)
    double mRotation = 0;

public:
    /// Default constructor (disabled)
    Harold() = delete;

    /// Copy constructor (disabled)
    Harold(const Harold &) = delete;

    /// Assignment operator
    void operator=(const Harold &) = delete;

    Harold(Game* game, const std::wstring &filename);

    void Update(double elapsed) override;

    void Draw(wxGraphicsContext *graphics) override;

    /**
    * Accept a visitor
     * @param visitor The visitor we accept
    */
    virtual void Accept(ItemVisitor* visitor) override { visitor->VisitHarold(this); }

};

#endif //PROJECT1_HAROLD_H
