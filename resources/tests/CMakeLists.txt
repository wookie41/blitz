project(blitz-resources-tests)

set(UNIT_TEST_LIST
        RefCountedResourceManager)

foreach (NAME IN LISTS UNIT_TEST_LIST)
    list(APPEND UNIT_TEST_SOURCE_LIST
            ${NAME}.test.cpp)
endforeach ()

enable_testing()
add_executable(${PROJECT_NAME}
        main.cpp
        ${UNIT_TEST_SOURCE_LIST})

target_link_libraries(${PROJECT_NAME} blitz-resources testkit)

add_test(${PROJECT_NAME} ${PROJECT_NAME})
mathfu_configure_flags(${PROJECT_NAME})