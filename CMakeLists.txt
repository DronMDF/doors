CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(doorsutil)

FIND_PACKAGE(Threads)

INCLUDE(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

ENABLE_TESTING()

ADD_COMPILE_OPTIONS(-std=c++17 -O2 -fomit-frame-pointer -g0
	-Wall -Wextra -Wpedantic -Werror
	-Wno-non-virtual-dtor)

ADD_EXECUTABLE(
	doorsutil
	main.cpp
)

TARGET_LINK_LIBRARIES(
	doorsutil
	${CMAKE_THREAD_LIBS_INIT}
)

INSTALL(
	TARGETS doorsutil
	RUNTIME DESTINATION bin
)

ADD_CUSTOM_TARGET(
	style
	COMMAND ${CMAKE_SOURCE_DIR}/style.sh
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
