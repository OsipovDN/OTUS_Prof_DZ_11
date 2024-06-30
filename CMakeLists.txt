
cmake_minimum_required (VERSION 3.20)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_NAME  "join_server")
set(TEST_NAME "join_server_test")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries")
set(TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

file(GLOB SOURCES CONFIGURE_DEPENDS
    "${SRC_DIR}/*.cpp"
    "${SRC_DIR}/Server/*.cpp"
    "${SRC_DIR}/Storage/*.cpp"
    "${LIB_DIR}/SQLite/*.c"
    )

project (${PROJECT_NAME} VERSION ${PROJECT_VESRION})

if (MSVC)
	# enable VS-Solution filters support
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif (MSVC)

# builds
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "Create separate directory for build.")
endif()
if (POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
endif()

add_executable (${PROJECT_NAME} ${SOURCES})
add_executable(${TEST_NAME}
    ${TEST_DIR}/join_server_test.cpp
    )

set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
 )

 set_target_properties(${TEST_NAME} PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
 )

  target_include_directories(${PROJECT_NAME} PUBLIC
    ${SRC_DIR}
    ${SRC_DIR}/Server
    ${SRC_DIR}/Storage
    ${LIB_DIR}/SQLite
    )

# link libraries
 # Boost
 find_package (Boost 1.83 REQUIRED COMPONENTS system thread)
if(Boost_FOUND)
  target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})
  target_link_libraries (${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
endif()

# GTest
find_package(GTest)
if(GTest_FOUND)
target_include_directories(${TEST_NAME} 
	    PRIVATE
	    ${SRC_DIR}
        ${TEST_DIR}
	    ${GTEST_INCLUDE_DIR}
 	    )
target_link_libraries(${TEST_NAME} PRIVATE ${GTEST_BOTH_LIBRARIES})
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE
        /EHsc
        /W4
        /WX
    )

endif()

# deb pkg
if (UNIX)
    install(TARGETS ${TEST_NAME} RUNTIME DESTINATION bin)

    set(CPACK_GENERATOR DEB)

    set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
    set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
    set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

    include(CPack)
endif (UNIX)
enable_testing()

add_test(${TEST_NAME} join_server_test)

