/**
 * @file MessageGettingVistior.h
 * @author Zachary Troxell
 *
 * Describes getting a message for Removal from the game
 */

#ifndef PROJECT1_MESSAGEGETTINGVISTIOR_H
#define PROJECT1_MESSAGEGETTINGVISTIOR_H

#include "ItemVisitor.h"

/**
 * Gets a message for a particular Item that is being removed from the Game
 */
class MessageGettingVistior : public ItemVisitor
{
private:
    ///The message from the Item
    wxString mMessage;
public:

    void VisitDropDown(DropDown* dropDown) override;

    void VisitSpeedBoost(SpeedBoost* speedBoost) override;

    void VisitClearScreen(ClearScreenPU *clearScreen) override;

    /**
     * Get the message from the desired item
     * @return the message from the item
     */
    wxString GetMessage() { return  mMessage; }
};

#endif //PROJECT1_MESSAGEGETTINGVISTIOR_H
