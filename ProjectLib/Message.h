/**
 * @file Message.h
 * @author Zachary Troxell
 *
 * A class that describes a removal message for an item
 */

#ifndef PROJECT1_MESSAGE_H
#define PROJECT1_MESSAGE_H

#include "Item.h"

/**
 * A message to be displayed while an item is being removed
 */
class Message : public Item
{
private:
    /// the item that needs a message to be displayed before removal
    std::shared_ptr<Item> mItemWithMessage;

    ///How many cycles since this message was created
    int mUpdateCycles;

    ///Whether or not the message needs to be removed.
    bool mRemoval = false;

    /// The output for the message on screen
    wxString mMessage = "";
public:
    /// Default constructor (disabled)
    Message() = delete;

    /// Copy constructor (disabled)
    Message(const Message &) = delete;

    /// Assignment operator
    void operator=(const Message &) = delete;

    Message(Game* game, std::shared_ptr<Item> item);

    void Update(double elapsed) override;

    void Draw(wxGraphicsContext *graphics) override;

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    virtual void Accept(ItemVisitor* visitor) override { visitor->VisitMessage(this); }

    /**
    * This Hit Test returns that it has been hit to be cleaned up after some time.
    * @param x X location on the game to test in pixels
    * @param y Y location on the game to test in pixels
    * @return true after a set number of game cycles
    */
    bool HitTest(int x, int y) override { return mRemoval; }
};

#endif //PROJECT1_MESSAGE_H
