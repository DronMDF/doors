CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(server-test)

ADD_EXECUTABLE(
	server-test
	test.cpp
	ActionRepr.cpp
	BytesRepr.cpp
	ConfigBytesTest.cpp
	ChainBytesTest.cpp
	DispatchedActionTest.cpp
	IdentBytesTest.cpp
	InventoryActionTest.cpp
	InventoryBytesTest.cpp
	KeyStatusBytesTest.cpp
	List32BytesTest.cpp
	List64BytesTest.cpp
	SaboteurStorage.cpp
	StatusActionTest.cpp
	TestAction.cpp
	TestSocket.cpp
	TestStorage.cpp
)

TARGET_LINK_LIBRARIES(
	server-test
	core
	${CONAN_LIBS}
)

ADD_CUSTOM_COMMAND(
	TARGET server-test
	PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/test-results/2out
)

ADD_TEST(
	NAME server-test
	COMMAND sh -c "${CMAKE_BINARY_DIR}/bin/server-test > ${CMAKE_BINARY_DIR}/test-results/server-test.xml"
)
