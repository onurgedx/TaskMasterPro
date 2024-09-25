cmake_minimum_required(VERSION 3.16)

project(TaskMasterPro VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt and necessary components including SQL
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Sql)

set(TS_FILES TaskMasterPro_en_001.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${TS_FILES}
)

set(EDIT_TASK_SOURCES
    src/edit_task_src/edittaskwindow.h
    src/edit_task_src/edittaskwindow.cpp
    src/edit_task_src/edittaskwindow.ui
)

set(TASK_MODAL_SOURCES
    src/task/Task.h
    src/task/Task.cpp
)

set(SURE2MOVE_TASK_WINDOW_SOURCES
    src/sure2move_task_window/suretoremovetaskwindow.h
    src/sure2move_task_window/suretoremovetaskwindow.cpp
    src/sure2move_task_window/suretoremovetaskwindow.ui
)

set(TASK_MANAGER_SOURCES
        src/task_manager/TaskManager.h
        src/task_manager/TaskManager.cpp
)

set(TASK_STORE_MANAGER_SOURCES
    src/task_store_manager/TaskStoreManager.h
    src/task_store_manager/TaskStoreManager.cpp
)

set(SURE2DELETE_ALL_TASKS_SOURCES
    src/sure2delete_alltasks/suretodeletealltasks.h
    src/sure2delete_alltasks/suretodeletealltasks.cpp
    src/sure2delete_alltasks/suretodeletealltasks.ui
)

set(WHOLE_TASK_LIST_WINDOW
    src/whole_task_list_window/wholetasklistwindow.h
    src/whole_task_list_window/wholetasklistwindow.cpp
    src/whole_task_list_window/wholetasklistwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TaskMasterPro
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${TASK_MODAL_SOURCES}
        ${EDIT_TASK_SOURCES}
        ${SURE2MOVE_TASK_WINDOW_SOURCES}
        ${TASK_MANAGER_SOURCES}
        ${TASK_STORE_MANAGER_SOURCES}
        ${SURE2DELETE_ALL_TASKS_SOURCES}
        ${WHOLE_TASK_LIST_WINDOW}

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TaskMasterPro APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(TaskMasterPro SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(TaskMasterPro
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

# Link necessary libraries including Qt SQL
target_link_libraries(TaskMasterPro PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TaskMasterPro)
endif()

set_target_properties(TaskMasterPro PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS TaskMasterPro
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TaskMasterPro)
endif()
