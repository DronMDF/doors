CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(doors-server)

FIND_PACKAGE(Threads)

ADD_COMPILE_OPTIONS(
	-std=c++17
	-O2
	-g0
	-fomit-frame-pointer
	-Wall
	-Werror
	-Wextra
	-Wpedantic
	-Wno-non-virtual-dtor
)

ADD_EXECUTABLE(
	doors-server
	main.cpp
)

TARGET_LINK_LIBRARIES(
	doors-server
	core
	${CMAKE_THREAD_LIBS_INIT}
	${CONAN_LIBS}
)

INSTALL(
	TARGETS doors-server
	RUNTIME DESTINATION bin
)
