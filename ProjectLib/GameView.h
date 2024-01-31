/**
 * @file GameView.h
 * @author Team Grady Win (Rajaditya Shrikishan Bajaj)
 *
 * View Class for our game
 */

#ifndef PROJECT1_GAMEVIEW_H
#define PROJECT1_GAMEVIEW_H

#include "Game.h"
#include "UMLData.h"

/**
 * View Class for our Game
 */
class GameView : public wxWindow
{
private:
    ///The game in which will be displayed and played upon
    Game mGame;

    /// The timer that allows for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;

    void OnViewStandard(wxCommandEvent& event);

    void OnUpdateViewStandard(wxUpdateUIEvent& event);

    void OnViewCustom(wxCommandEvent& event);

    void OnUpdateViewCustom(wxUpdateUIEvent& event);

    void OnPaint(wxPaintEvent& event);

    void OnMouseMove(wxMouseEvent& event);

    void OnTimer(wxTimerEvent& event);

public:

    void Initialize(wxFrame* parent, Game* game);

    void AddMenus(wxFrame* mainFrame, wxMenuBar* menuBar, wxMenu* variableMenu);

    void OnLeftDown(wxMouseEvent& event);

    /**
     * Stop the timer so the window can close
     */
    void Stop() {mTimer.Stop();}
};

#endif //PROJECT1_GAMEVIEW_H
