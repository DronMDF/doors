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
	BootstrapTask.cpp
	BytesInventory.cpp
	BytesOk.cpp
	ConfigBytes.cpp
	ChainBytes.cpp
	DefaultStorage.cpp
	DispatchedAction.cpp
	IdentBytes.cpp
	ImmediatlyScheduler.cpp
	InventoryAction.cpp
	InventoryBytes.cpp
	InventoryTask.cpp
	KeyStatusBytes.cpp
	List32Bytes.cpp
	List64Bytes.cpp
	Listener.cpp
	NullStorage.cpp
	StatusAction.cpp
	StatusTask.cpp
)
