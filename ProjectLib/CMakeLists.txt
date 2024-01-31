project(ProjectLib)




set(SOURCE_FILES MainFrame.cpp MainFrame.h pch.h ids.h GameView.cpp GameView.h Game.cpp Game.h Item.cpp Item.h Scoreboard.h Scoreboard.cpp Harold.cpp Harold.h Marker.cpp Marker.h ItemVisitor.cpp ItemVisitor.h LaunchVisitor.cpp LaunchVisitor.h DropDown.cpp DropDown.h UMLData.cpp UMLData.h UMLValue.cpp UMLValue.h SpeedBoost.cpp SpeedBoost.h BoostSpeedVisitor.cpp BoostSpeedVisitor.h GreenMarker.cpp GreenMarker.h RedMarker.cpp RedMarker.h HaroldImage.cpp HaroldImage.h Message.cpp Message.h MessageGettingVistior.cpp MessageGettingVistior.h ClearScreenPU.cpp ClearScreenPU.h DropDownVisitor.cpp DropDownVisitor.h Bob.cpp Bob.h)




set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)
