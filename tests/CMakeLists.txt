file(GLOB TEST_SRCS "*.cpp")

find_package(GTest REQUIRED)

include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})

foreach(SRC_FILE ${TEST_SRCS})
  get_filename_component(TEST_NAME ${SRC_FILE} NAME_WE)
  add_executable(${TEST_NAME} ${SRC_FILE})
  target_link_libraries(${TEST_NAME} ${GTEST_BOTH_LIBRARIES} smoc)
  add_test(${TEST_NAME} ${TEST_NAME})
endforeach()
