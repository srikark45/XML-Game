/**
 * @file ItemVisitor.h
 * @author Team Grady Wins (Zachary Troxell)
 *
 * Item Visitor Base class.
 */

#ifndef PROJECT1_ITEMVISITOR_H
#define PROJECT1_ITEMVISITOR_H

class Marker;
class Harold;
class Scoreboard;
class DropDown;
class SpeedBoost;
class Message;
class ClearScreenPU;
/**
 * Item visitor base class
 */
class ItemVisitor
{
public:
    /// Destructs ItemVisitor
    virtual ~ItemVisitor() {}

    /**
     * Visit a Marker
     * @param marker Marker we are visiting
     */
     virtual void VisitMarker(Marker* marker) {}

    /**
     * Visit a Harold
     * @param harold Harold we are visiting
     */
    virtual void VisitHarold(Harold* harold) {}

    /**
     * Visit a ScoreBoard
     * @param scoreboard Scoreboard we are visiting
     */
    virtual void VisitScoreboard(Scoreboard* scoreboard) {}

    /**
     * Visit a Dropdown box
     * @param dropDown DropDown we are visiting
     */
    virtual void VisitDropDown(DropDown* dropDown) {}

    /**
     * Visit a SpeedBoost box
     * @param speedBoost SpeedBoost we are visiting
     */
    virtual void VisitSpeedBoost(SpeedBoost* speedBoost) {}

    /**
     * Visit a ClearScreen box
     * @param clearScreen SpeedBoost we are visiting
     */
    virtual void VisitClearScreen(ClearScreenPU* clearScreen) {}

    /**
     * Visit a message
     * @param message Message we are visiting
     */
    virtual void VisitMessage(Message* message) {}
};

#endif //PROJECT1_ITEMVISITOR_H
