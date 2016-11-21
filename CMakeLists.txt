cmake_minimum_required(VERSION 3.3)
project(MPACK)

if (WIN32)
    add_custom_target(MPACK ALL COMMAND make -f "jni/Windows.mk" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif (WIN32)

if (UNIX)
    add_custom_target(MPACK ALL COMMAND make -f "jni/Linux.mk" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif (UNIX)

if (APPLE)
    add_custom_target(MPACK ALL COMMAND make -f "jni/OSX.mk" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif (APPLE)
