
SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

PROJECT(main)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

IF (UNIX)
	MESSAGE(STATUS "	unix:" ${UNIX})
	MESSAGE(STATUS "	compiler path:" ${CMAKE_TOOLCHAIN_FILE})
	MESSAGE(STATUS "	current_source_dir:" ${CMAKE_CURRENT_SOURCE_DIR})
	MESSAGE(STATUS "	binary_dir:" ${CMAKE_BINARY_DIR})
ELSEIF (APPLE)
	MESSAGE(STATUS "	apple:" ${UNIX})
ELSE()
	MESSAGE(STATUS "	win32:" ${UNIX})
ENDIF()

SET(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/usr/local")

SET(CMAKE_BUILD_TYPE "Debug" CACHE STRING "set build type to debug")

INCLUDE_DIRECTORIES("${CMAKE_BINARY_DIR}/include/")

OPTION(HAVE_PL_TEST1 "test macro control" off)

CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/cmake/templates/hello.h.in" 
			"${CMAKE_BINARY_DIR}/include/hello.h")

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
	MESSAGE(STATUS "debug mode")
else()
	MESSAGE(STATUS "release mode")
endif()


AUX_SOURCE_DIRECTORY(. DIR_SRCS)
ADD_EXECUTABLE(main ${DIR_SRCS})

MESSAGE(STATUS "	install path:" ${CMAKE_INSTALL_PREFIX})
MESSAGE(STATUS "	cmake system:" ${CMAKE_SYSTEM})
MESSAGE(STATUS "	cmake system processer:" ${CMAKE_SYSTEM_PROCESSOR})
MESSAGE(STATUS "	loop:" ${CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS})

INSTALL(TARGETS main DESTINATION ${CMAKE_INSTALL_PREFIX})
INSTALL(DIRECTORY "${CMAKE_BINARY_DIR}/include" DESTINATION ${CMAKE_INSTALL_PREFIX} FILES_MATCHING PATTERN "*.h")

IF (DEFINED HAVE_PL_TEST1)
	MESSAGE(STATUS "define HAVE_PL_TEST1")
ElSE()
	MESSAGE(STATUS "nodefine HAVE_PL_TEST1")
ENDIF()

IF(HAVE_PL_TEST1)
	MESSAGE(STATUS "HAVE_PL_TEST1 on")
ElSE()
	MESSAGE(STATUS "HAVE_PL_TEST1 off")
ENDIF()

