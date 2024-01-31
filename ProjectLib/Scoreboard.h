/**
 * @file Scoreboard.h
 * @author Nathaniel
 *
 * The class that is responsible for displaying
 *  the scoreboard.
 */

#ifndef PROJECT1_SCOREBOARD_H
#define PROJECT1_SCOREBOARD_H
#include "Item.h"
#include <wx/dcbuffer.h>

/**
 * Describes information for the scoreboard.
 */
class Scoreboard : public Item
{
private:
    /// Number of bad UML boxes hit
    int mCorrect = 0;

    /// Number of bad UML boxes missed
    int mMissed = 0;

    /// Number of correct UML boxes hit
    int mUnfair = 0;

public:

    /// Default constructor (disabled)
    Scoreboard() = delete;

    /// Copy constructor (disabled)
    Scoreboard(const Scoreboard &) = delete;

    /// Assignment operator
    void operator=(const Scoreboard &) = delete;

    Scoreboard(Game* game);

    /**
     * The correct score of the game
     * @return Correct score in int
     */
    int GetCorrect() const { return mCorrect; }

    /**
     * The missed score of the game
     * @return Missed score in int
     */
    int GetMissed() const { return mMissed; }

     /**
      * The unfair score of the game
      * @return Unfair score in int
      */
     int GetUnfair() const { return mUnfair; }

     /**
      * Increments correct score by one
      */
     void IncCorrect() { mCorrect++; }

     /**
      * Increments missed score by one
      */
     void IncMissed() { mMissed++; }

     /**
      * Increments unfair score by one
      */
     void IncUnfair() { mUnfair++; }


    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    virtual void Accept(ItemVisitor* visitor) override { visitor->VisitScoreboard(this); }

    /**
    * Draws the scoreboard with the number values centered over the names
    * @param graphics use to draw on screen
    * @param word name of the scoreboard value
    * @param x x-value
    * @param y y-value
    */
    void placeTextCentered(wxGraphicsContext *graphics, std::string word, double x, double y);

    /**
    * Draws the scoreboard
    * @param graphics use to draw on screen
    */
    void Draw(wxGraphicsContext *graphics) override;
};

#endif //PROJECT1_SCOREBOARD_H
