find_package(Boost REQUIRED)

add_library(smoc STATIC
  smoc/object.cpp)
target_include_directories(smoc INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${Boost_INCLUDE_DIRS})
