/**
 * @file SpeedBoost.h
 * @author Zachary Troxell
 *
 * Describes the speed boost power up
 */

#ifndef PROJECT1_SPEEDBOOST_H
#define PROJECT1_SPEEDBOOST_H

#include "Item.h"
/**
 * Description of a SpeedBoost Power up
 */
class SpeedBoost : public Item
{
private:
    /// The SpeedBoost image
    std::unique_ptr<wxImage> mItemImage;

    /// The SpeedBoost bitmap
    std::unique_ptr<wxBitmap> mItemBitmap;

    ///Speed in the x Direction
    double mSpeedX;

    ///Speed in the y Direction
    double mSpeedY;

    /// Acceleration in the x direction in pixels a second
    double mAccelerationX;

    /// Indication if the SpeedBoost has fallen through the bottom of the screen
    bool mOutOfBounds = false;

public:
    /// Default constructor (disabled)
    SpeedBoost() = delete;

    /// Copy constructor (disabled)
    SpeedBoost(const SpeedBoost &) = delete;

    /// Assignment operator
    void operator=(const SpeedBoost &) = delete;

    SpeedBoost(Game* game);

    void Update(double elapsed) override;

    void Draw(wxGraphicsContext *graphics) override;

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    virtual void Accept(ItemVisitor* visitor) override { visitor->VisitSpeedBoost(this); }

    /**
     *  Tells if the Speed Boost has fallen through the bottom
     *  @return
     */
    bool OutOfBounds() override { return mOutOfBounds; }

    bool HitTest(int x, int y) override;

    void SetLocation(double x, double y) override;

    void RemoveBehavior() override;

};

#endif //PROJECT1_SPEEDBOOST_H
