/**
 * @file ProjectApp.cpp
 * @author Team Grady Win (Rajaditya Shrikishan Bajaj)
 */

#include "pch.h"
#include <MainFrame.h>
#include "ProjectApp.h"

/**
 * Initialize the application.
 * @return
 */
bool ProjectApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;
}