find_package(Boost COMPONENTS system REQUIRED)

include_directories(smoc)

add_library(smoc STATIC
  smoc/object.cpp
  smoc/event_loop.cpp)
target_include_directories(smoc SYSTEM PUBLIC ${Boost_INCLUDE_DIRS})
target_include_directories(smoc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(smoc ${Boost_LIBRARIES})
if(BUILD_SHARED_LIBS)
  target_compile_definitions(smoc PUBLIC -DBOOST_ALL_DYN_LINK)
endif()

if(WIN32)
  target_link_libraries(smoc ws2_32)
endif()
