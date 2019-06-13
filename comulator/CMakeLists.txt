CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(comulator)

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
	comulator
	main.cpp
	Benchmark.cpp
	LockTask.cpp
	LockTaskHandler.cpp
	UnlockTask.cpp
)

TARGET_LINK_LIBRARIES(
	comulator
	core
	${CMAKE_THREAD_LIBS_INIT}
	${CONAN_LIBS}
)

INSTALL(
	TARGETS comulator
	RUNTIME DESTINATION bin
)
