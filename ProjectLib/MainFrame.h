/**
 * @file MainFrame.h
 * @author Team Grady Win (Rajaditya Shrikishan Bajaj)
 *
 * Class that is the top frame of the application
 */

#ifndef PROJECT1_MAINFRAME_H
#define PROJECT1_MAINFRAME_H

#include "Game.h"

class GameView;
/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:
    ///The game in which will be displayed and played upon
    Game mGame;

    /// The view for the game
    GameView* mGameView;

public:

    void Initialize();

    void OnExit(wxCommandEvent& event);

    void OnAbout(wxCommandEvent&);
};

#endif //PROJECT1_MAINFRAME_H
