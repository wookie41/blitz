project (common)
file(WRITE null.cpp "")

add_library(${PROJECT_NAME} STATIC null.cpp)
add_library(blitz::common ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
        INTERFACE
        ${PROJECT_SOURCE_DIR}/include
)

mathfu_configure_flags(${PROJECT_NAME})