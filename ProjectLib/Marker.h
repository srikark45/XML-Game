/**
 * @file Marker.h
 * @author Nathaniel
 *
 * Base class of the Marker
 */

#ifndef PROJECT1_MARKER_H
#define PROJECT1_MARKER_H

#include "Item.h"
#include "cmath"

/**
 * Base class of the marker
 */
class Marker : public Item
{
private:

    /// The item image
    std::shared_ptr<wxImage> mItemImage;

    /// The item bitmap
    wxGraphicsBitmap mItemBitmap;

    /// Current rotation (in radians)
    double mRotation = 0;

    /// Whether the marker is launched from Harold
    bool mLaunched = false;

    /// Target trajectory
    double mTrajectory;

    /// if variant
    bool mVariant = false;

    /// if boosted
    bool mBoosted = false;

    /// the offset required for the marker
    double mOffSet;

    /// Distance from arm to marker
    double mArmDistance;

    /// Speed of the marker
    double mSpeed;

    /// SpeedFactor of marker speed boost
    double mDuration = 0;

public:
    /// Default constructor (disabled)
    Marker() = delete;

    /// Copy constructor (disabled)
    Marker(const Marker &) = delete;

    /// Assignment operator
    void operator=(const Marker &) = delete;

    Marker(Game* game, const std::wstring &filename, const bool &variant );

    void Update(double elapsed) override;

    void Draw(wxGraphicsContext *graphics) override;

    void Launch();

    void SpeedBoost();

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    virtual void Accept(ItemVisitor* visitor) override { visitor->VisitMarker(this); }
};

#endif //PROJECT1_MARKER_H
