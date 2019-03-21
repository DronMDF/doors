CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(server-test)

ADD_EXECUTABLE(
	server-test
	test.cpp
	ActionRepr.cpp
	StatusActionTest.cpp
	TestSocket.cpp
	TestStorage.cpp
)

TARGET_LINK_LIBRARIES(
	server-test
	server-core
	2out
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
