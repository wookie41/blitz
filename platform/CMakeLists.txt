cmake_minimum_required(VERSION 3.12)
project (blitz-platform)

add_library(${PROJECT_NAME} STATIC
        src/event/SDLEventPooler.cpp 
        src/input/SDLInputManager.cpp)

add_library(blitz::platform ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} blitz::common)
mathfu_configure_flags(${PROJECT_NAME})
