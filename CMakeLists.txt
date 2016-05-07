cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME stereogram)
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(CMAKE_BUILD_TYPE Debug)
project( ${PROJECT_NAME} )

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set (CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -g -std=c++11") 

# Versioning
# Replace @VARIABLES@ with CMake values
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/.version.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/version.hpp"
  )

MESSAGE( "${CMAKE_MODULE_PATH}" )

# Source
file(GLOB_RECURSE  
	   Project_SOURCES
     ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    )
add_executable( ${PROJECT_NAME} ${Project_SOURCES} )


########################### Libraries ##########################################

# OpenGL

set(OpenCV_DIR "/usr/local/build/opencv-3.1.0")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
# if (OPENCV_FOUND)
  target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
  target_link_libraries(${PROJECT_NAME} m)  # if using maths.h

  MESSAGE( "Found OpenCV")
# endif()


# # Create installer
# include(InstallRequiredSystemLibraries)
# set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
# set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
# set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
# set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "My funky project")
# set(CPACK_PACKAGE_VENDOR "Thibault Lucidarme")
# set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.txt")
# set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/Copyright.txt")
# if(WIN32 AND NOT UNIX)
#   # There is a bug in NSI that does not handle full unix paths properly. Make
#   # sure there is at least one set of four (4) backlasshes.
#   set(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}\\\\InstallIcon.bmp")
#   set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\${PROJECT_NAME}.exe")
#   set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} My Famous Project")
#   set(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\github.com\\\\ThibaultLucidarme?tab=repositories")
#   set(CPACK_NSIS_CONTACT "me@my-personal-home-page.com")
#   set(CPACK_NSIS_MODIFY_PATH ON)
# else(WIN32 AND NOT UNIX)
#   set(CPACK_STRIP_FILES "bin/${PROJECT_NAME}")
#   set(CPACK_SOURCE_STRIP_FILES "")
# endif(WIN32 AND NOT UNIX)
# set(CPACK_PACKAGE_EXECUTABLES ${PROJECT_NAME} ${PROJECT_NAME})
# include(CPack)
