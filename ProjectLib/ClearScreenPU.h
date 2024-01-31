/**
 * @file ClearScreenPU.h
 * @author Ian Hay
 * Describes the Clear screen power up
 */

#ifndef PROJECT1_CLEARSCREENPU_H
#define PROJECT1_CLEARSCREENPU_H

#include "Item.h"

/// Description of a clear screen power up
class ClearScreenPU : public Item
{
private:
    /// The ClearScreen image
    std::unique_ptr<wxImage> mItemImage;

    /// The ClearScreen bitmap
    std::unique_ptr<wxBitmap> mItemBitmap;

    ///Speed in the x Direction
    double mSpeedX;

    ///Speed in the y Direction
    double mSpeedY;

    /// Acceleration in the x directmOutOFion in pixels a second
    double mAccelerationX;

    /// Indication if the ClearScreenPU has fallen through the bottom of the screen
    bool mOutOfBounds = false;

public:
    /// Default constructor (disabled)
    ClearScreenPU() = delete;

    /// Copy constructor (disabled)
    ClearScreenPU(const ClearScreenPU &) = delete;

    /// Assignment operator
    void operator=(const ClearScreenPU &) = delete;

    ClearScreenPU(Game* game);

    void Update(double elapsed) override;

    void Draw(wxGraphicsContext *graphics) override;

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    virtual void Accept(ItemVisitor* visitor) override { visitor->VisitClearScreen(this); }

    /**
     *  Tells if the Speed Boost has fallen through the bottom
     *  @return
     */
    bool OutOfBounds() override { return mOutOfBounds; }

    bool HitTest(int x, int y) override;

    void SetLocation(double x, double y) override;

    void RemoveBehavior() override;

};


#endif //PROJECT1_CLEARSCREENPU_H
