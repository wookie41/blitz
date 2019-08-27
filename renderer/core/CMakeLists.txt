cmake_minimum_required(VERSION 3.12)
project(blitz-renderer-core)
set(CMAKE_CXX_STANDARD 17)

add_library(blitz-renderer-core src/Device.cpp)

target_include_directories(blitz-renderer-core PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

target_link_libraries(blitz-renderer-core PRIVATE mathfu)
target_link_libraries(blitz-renderer-core PRIVATE sdl2)

install(TARGETS blitz-renderer-core EXPORT BlitzRendererCoreConfig
        ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT BlitzRendererCoreConfig
        DESTINATION share/blitz-renderer-core/cmake)

export(TARGETS blitz-renderer-core FILE BlitzRendererCoreConfig.cmake)

##add_executable(blitz-renderer-core-tests) #TODO
#target_link_libraries(blitz-renderer-core-tests blitz-renderer-core)
#add_test(blitz-renderer-core-tests blitz-renderer-core-tests)