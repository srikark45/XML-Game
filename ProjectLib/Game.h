/**
 * @file Game.h
 * @author Zachary Troxell
 *
 * Describes the game
 */

#ifndef PROJECT1_GAME_H
#define PROJECT1_GAME_H

#include <memory>
#include <random>
#include <vector>
#include <wx/graphics.h>
#include <wx/xml/xml.h>
#include "UMLData.h"
#include "Scoreboard.h"
#include <typeinfo>

class Item;
class Marker;
class ItemVisitor;

/**
 * Description of a game
 */
class Game
{
private:
    /// The UML class that we need to store the game.
    UMLData mData;

    /// The items in which the game can display
    std::vector<std::shared_ptr<Item>> mItems;

    /// Scoreboard for the game.
    std::shared_ptr<Scoreboard> mScoreboard;

    ///Scale in which to be drawn in
    double mScale{};

    /// How far from the left hand side to start drawing
    double mXOffset{};

    /// How far from the top side to start drawing
    double mYOffset{};

    /// Random number generator
    std::mt19937 mRandom;

    /// Mouse x location
    int mMouseX{};

    /// Mouse y location
    int mMouseY{};

    /// Is Variant checked
    bool mVariant = false;

    /// Time elapsed
    double mElapsed = 0;

    /// The counter for boost speed
    double mSpeedBoostCounter = 0;

    /// The counter to clear screen
    double mClearScreenCounter = 0;

    /// The counter to add new dropdown box
    double mInterval = 0;

public:

    /**
     * Gets the random number generator
     * @return  random number generator
     */
    std::mt19937 &GetRandom() { return mRandom; };

    void OnDraw(wxGraphicsContext *graphics, int width, int height);

    Game();

    std::shared_ptr<Item> HitTest(int x, int y);

    void Add(const std::shared_ptr<Item>& item);

    void RemoveItem(std::shared_ptr<Item>& item);

    void Update(double elapsed);

    /// Game area in virtual pixels
    const static int Width = 1250;

    /// Game area height in virtual pixels
    const static int Height = 1000;

    void SetMouseLocation(int x, int y);

    /**
     * Get mMouseX
     * @return the value of mMouseX
     */
    int GetMouseX() const { return mMouseX; }

    /**
     * Get mMouseY
     * @return the value of mMouseY
     */
    int GetMouseY() const { return mMouseY; }

    /**
     * Get mXOffset
     * @return the value of mOffsetX
     */
    int GetOffsetX() const { return mXOffset; }

    /**
     * Get mYOffset
     * @return the value of mOffsetY
     */
    int GetOffsetY() const { return mYOffset; }

    /**
     * Get the current size of the screen in the Y direction
     * @return The size of the screen in the y direction in pixels
     */
    double GetScale() const { return mScale; }

    /**
     * Get the time elapsed since the game has started
     * @return time elapsed since game started
     */
    double GetElapsed() const { return mElapsed; }

    void Accept(ItemVisitor* visitor);

    void Launch(double xCoordinate, double yCoordinate);

    void Load(const wxString& filename);

    /**
     * This function returns the UML Data class
     * @return UMLData
     */
    UMLData GetData() { return mData; }

    void OutOfBoundsItem();

    void BoostMarkerSpeed();

    void SetVariant(bool variant);

    /**
     * Get the current Game state of variant or standard
     * @return true if Variant false otherwise
     */
    bool GetVariant() const {return mVariant;}

    void ClearUMLBoxes();

    void SetElapsed(double elapsed);

    void IncrementCorrect();

    void IncrementUnfair();

    void IncrementMissed();

    void RemoveItems();
};

#endif //PROJECT1_GAME_H
