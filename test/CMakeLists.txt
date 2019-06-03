CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(server-test)

ADD_EXECUTABLE(
	server-test
	test.cpp
	ActionRepr.cpp
	BytesRepr.cpp
	BootstrapTaskTest.cpp
	ConfigBytesTest.cpp
	ChainBytesTest.cpp
	DispatchedActionTest.cpp
	IdentBytesTest.cpp
	InventoryActionTest.cpp
	InventoryBytesTest.cpp
	InventoryTaskTest.cpp
	KeyStatusBytesTest.cpp
	List32BytesTest.cpp
	List64BytesTest.cpp
	LockBytesTest.cpp
	LogIoService.cpp
	LogStorage.cpp
	SaboteurStorage.cpp
	StatusActionTest.cpp
	TestAction.cpp
	TestUdpService.cpp
	TestSocket.cpp
)

TARGET_LINK_LIBRARIES(
	server-test
	core
	${CONAN_LIBS}
)

ADD_TEST(
	NAME server-test
	COMMAND sh -c "${CMAKE_BINARY_DIR}/bin/server-test > ${CMAKE_BINARY_DIR}/server-test-result.xml"
)
