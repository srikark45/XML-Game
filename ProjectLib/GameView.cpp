/**
 * @file GameView.cpp
 * @author Team Grady Win (Rajaditya Shrikishan Bajaj)
 */

#include "pch.h"

#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include <wx/string.h>

#include "Marker.h"
#include "ids.h"
#include "Harold.h"
#include "GameView.h"
#include "DropDown.h"

using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;

/// Translates the seconds into milliseconds
const double MillisecondTranslation = .001;

/**
 * Initialize the aquarium view class.
 * @param parent The parent window for this class
 * @param game The game in which to display
 */
void GameView::Initialize(wxFrame* parent, Game *game)
{
    Create(parent, wxID_ANY);
    SetBackgroundStyle(wxBG_STYLE_PAINT);


    Bind(wxEVT_PAINT, &GameView::OnPaint, this);
    Bind(wxEVT_MOTION, &GameView::OnMouseMove, this);
    Bind(wxEVT_LEFT_DOWN, &GameView::OnLeftDown, this);

    //
    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    mStopWatch.Start();

    Bind(wxEVT_TIMER, &GameView::OnTimer, this);

}
/**
 * Add menus specific to the view
 * @param mainFrame The main frame that owns the menu bar
 * @param menuBar The menu bar to add menus to
 * @param variableMenu The bar that shows custom or variant game is active
 * param viewMenu The view menu, so we can add to it if we wish **** add at sign later if we add viewMenu
 */
void GameView::AddMenus(wxFrame* mainFrame, wxMenuBar *menuBar, wxMenu* variableMenu)
{
    // Append to the Variable Menu
    variableMenu->Append(IDM_STANDARD, L"&Standard", L"Standard Option of game", wxITEM_CHECK);
    variableMenu->Append(IDM_VARIANT, L"&Custom", L"Custom Option of game", wxITEM_CHECK);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnViewStandard, this, IDM_STANDARD);
    mainFrame->Bind(wxEVT_UPDATE_UI, &GameView::OnUpdateViewStandard, this, IDM_STANDARD);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnViewCustom, this, IDM_VARIANT);
    mainFrame->Bind(wxEVT_UPDATE_UI, &GameView::OnUpdateViewCustom, this, IDM_VARIANT);

}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto gc = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));

    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * MillisecondTranslation;
    mTime = newTime;
    
    mGame.Update(elapsed);
    mGame.SetElapsed(elapsed);

    wxRect rect = GetRect();
    mGame.OnDraw(gc.get(), rect.GetWidth(), rect.GetHeight());
}

/**
 * Menu event handler variant>standard menu option
 * @param event Menu event
 */
void GameView::OnViewStandard(wxCommandEvent& event)
{
    mGame.SetVariant(false);    // we are in standard state
}

/**
 * Update handler for Variant>Standard menu option
 * @param event Update event
 */
void GameView::OnUpdateViewStandard(wxUpdateUIEvent& event)
{
    if (mGame.GetVariant())
    {
        event.Check(false); // no variant state
    }
    else
    {
        event.Check(true);  // in variant state
    }
}

/**
 * Menu event handler variant>custom menu optino
 * @param event Menu event
 */
void GameView::OnViewCustom(wxCommandEvent& event)
{
    mGame.SetVariant(true);
}

/**
 * Update handler for Variant>custom menu option
 * @param event Update event
 */
void GameView::OnUpdateViewCustom(wxUpdateUIEvent& event)
{
    if (mGame.GetVariant())
    {
        event.Check(true);
    }
    else
    {
        event.Check(false);
    }
}

/**
* Handle the mouse move event
* @param event
*/
void GameView::OnMouseMove(wxMouseEvent &event)
{
    mGame.SetMouseLocation(event.GetX(), event.GetY());
    Refresh();

}

/**
* Handle the mouse down event
* @param event
*/
void GameView::OnLeftDown(wxMouseEvent &event)
{
    mGame.Launch(event.GetX(), event.GetY());
    Refresh();

}

/**
* Event handler for timer
 * @param event Timer event
*/
void GameView::OnTimer(wxTimerEvent& event)
{
    Refresh();
}

