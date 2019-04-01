CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(core)

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
	core
	AsioSocket.cpp
	DefaultStorage.cpp
	DispatchedAction.cpp
	ImmediatlyScheduler.cpp
	InventoryAction.cpp
	Listener.cpp
	NullStorage.cpp
	StatusAction.cpp
	StatusTask.cpp
)
