find_package(PkgConfig)
if(PKG_CONFIG_FOUND)
  pkg_check_modules(LIBZMQ libzmq)
  pkg_check_modules(LIBMSGPACK msgpack)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(LIBZMQ_FOUND AND LIBMSGPACK_FOUND)
  add_library(rpc-lib INTERFACE)
  target_include_directories(rpc-lib INTERFACE
    rpc
    ${LIBZMQ_INCLUDE_DIRS} ${LIBMSGPACK_INCLUDE_DIRS})
  target_link_libraries(rpc-lib INTERFACE
    ${LIBZMQ_LIBRARIES} ${LIBMSGPACK_LIBRARIES})

  smoc_generate(${CMAKE_CURRENT_SOURCE_DIR}/rpc/rpc-base.h
    ${CMAKE_CURRENT_SOURCE_DIR}/rpc/rpc-common.hpp.tmpl
    rpc-common.hpp)

  smoc_generate(${CMAKE_CURRENT_SOURCE_DIR}/rpc/rpc-base.h
    ${CMAKE_CURRENT_SOURCE_DIR}/rpc/rpc-server.hpp.tmpl
    rpc-server.hpp)
  add_executable(rpc-server rpc/main-server.cpp
    rpc-server.hpp rpc-common.hpp)
  target_link_libraries(rpc-server rpc-lib)

  smoc_generate(${CMAKE_CURRENT_SOURCE_DIR}/rpc/rpc-base.h
    ${CMAKE_CURRENT_SOURCE_DIR}/rpc/rpc-client.cpp.tmpl
    rpc-client.cpp)
  add_executable(rpc-client rpc/main-client.cpp
    rpc-client.cpp rpc-common.hpp)
  target_link_libraries(rpc-client rpc-lib)
endif()
