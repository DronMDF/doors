CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(server-core)

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

ADD_LIBRARY(
	server-core
	DefaultStorage.cpp
	ImmediatlyScheduler.cpp
	NullStorage.cpp
	StatusAction.cpp
	StatusTask.cpp
)
