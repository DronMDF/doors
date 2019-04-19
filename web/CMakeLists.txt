CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# @todo #74 Добавить coverage в web
ADD_TEST(
	NAME web-test
	COMMAND ${CMAKE_SOURCE_DIR}/web/manage.py test --settings=web.test_settings doors.tests
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
