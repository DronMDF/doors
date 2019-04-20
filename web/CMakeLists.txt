CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_TEST(
	NAME web-test
	COMMAND coverage run ${CMAKE_SOURCE_DIR}/web/manage.py test --settings=web.test_settings doors.tests
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
