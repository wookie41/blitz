project(blitz-memory C CXX)

add_library(${PROJECT_NAME} SHARED 
	src/Heap.cpp
    src/Precompiled.cpp
)
add_library(blitz::memory ALIAS ${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        CMAKE_CXX_STANDARD 17
        LINKER_LANGUAGE CXX)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} blitz::common)

if(WITH_DEBUG_TOOLS)
    target_link_libraries(${PROJECT_NAME} loguru)
endif()

add_compile_definitions(USE_LIBC_MALLOC)
mathfu_configure_flags(${PROJECT_NAME})
