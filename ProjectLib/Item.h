/**
 * @file Item.h
 * @author Team Grady Wins
 *
 * Base class for all the items
 */

#ifndef PROJECT1_ITEM_H
#define PROJECT1_ITEM_H

#include <memory>
#include <wx/filename.h>
#include <wx/graphics.h>

#include "ItemVisitor.h"

class Game;

/**
 * Base class for all the items
 */
class Item
{
private:

    /// The game this item is contained in
    Game *mGame;

    /// Item location in the game
    double  mX = 0;     ///< X location for the center of the item
    double  mY = 0;     ///< Y location for the center of the item

    /// Whether or not the game needs to be removed
    bool mRemove = false;

public:
    virtual ~Item();

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    /// Assignment operator
    void operator=(const Item &) = delete;

    /**
     * The X location of the item
     * @return X location in pixels
     */
    double GetX() const { return mX; }

    /**
     * The Y location of the item
     * @return Y location in pixels
     */
    double GetY() const { return mY; }

    /**
    * Handle updates for animation
    * @param elapsed The time since the last update
    */
    virtual void Update(double elapsed) {  }

    /**
    * Draw the item
    * @param graphics The graphics context to draw on
    */
    virtual void Draw(wxGraphicsContext *graphics);

    /**
    * Test this item to see if it has been hit
    * @param x X location on the game to test in pixels
    * @param y Y location on the game to test in pixels
    * @return true if hit
    */
    virtual bool HitTest(int x, int y) { return false; }

    /**
    * Test this item to see if it has gone out of bounds
    * @return true if out of bounds
    */
    virtual bool OutOfBounds() { return false; }


    /**
     * Get the pointer to the Game object
    * @return Pointer to Game object
    */
    Game *GetGame() { return mGame;  }

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    virtual void Accept(ItemVisitor* visitor) = 0;

    /**
     * Behavior on removal to be overridden
     */
    virtual void RemoveBehavior() {};

    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    virtual void SetLocation(double x, double y) { mX = x; mY = y; }

    /**
     * Set the remove value for being removed from the game
     * @param remove Whether or not to remove the item from the game
     */
    void SetRemove(bool remove) { mRemove = remove; }

    /**
     *
     * @return
     */
    bool GetRemove() const { return mRemove; }

protected:
    /// pointer to the game builder for the items we would add in game.
    Item(Game *game);
};

#endif //PROJECT1_ITEM_H
