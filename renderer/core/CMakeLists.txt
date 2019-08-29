project (renderer-core)

add_library(${PROJECT_NAME} STATIC src/Device.cpp)
add_library(blitz::renderer-core ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include
        )

target_link_libraries(renderer-core blitz::common)

##add_executable(blitz-renderer-core-tests) #TODO
#target_link_libraries(blitz-renderer-core-tests blitz-renderer-core)
#add_test(blitz-renderer-core-tests blitz-renderer-core-tests)