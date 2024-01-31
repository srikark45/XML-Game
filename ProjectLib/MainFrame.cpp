/**
 * @file MainFrame.cpp
 * @author Team Grady Win (Rajaditya Shrikishan Bajaj)
 *
 * This class initializes the Main Frame
 */

#include "pch.h"

#include "GameView.h"
#include "MainFrame.h"
#include "Game.h"

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    mGame = Game();
    Create(nullptr, wxID_ANY, L"UML Wars",
            wxDefaultPosition,  wxSize( mGame.Width,mGame.Height ));

    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer( wxVERTICAL );

    // Create the view class object as a child of MainFrame
    auto gameView = new GameView();
    gameView->Initialize(this, &mGame);

    // Add it to the sizer
    sizer->Add(gameView,1, wxEXPAND | wxALL );

    // Set the sizer for this frame
    SetSizer( sizer );

    // Layout (place) the child windows.
    Layout();

    CreateStatusBar();

    auto menuBar = new wxMenuBar( );

    auto fileMenu = new wxMenu();
    auto variantMenu = new wxMenu();
    auto helpMenu = new wxMenu();

    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);

    menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(variantMenu, L"&Variant");
    gameView->AddMenus(this, menuBar, variantMenu);
    menuBar->Append(helpMenu, L"&Help");

    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

    SetMenuBar( menuBar );
}


/**
 * Exit menu option handlers
 * @param event the handler
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    mGameView->Stop();
    Destroy();
}

/**
* Application about box menu handler
*/
void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(L"Welcome to the UML Wars!",
            L"About UML Wars",
            wxOK,
            this);
}