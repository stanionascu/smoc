project(smoc)
cmake_minimum_required(VERSION 3.4)
enable_language(CXX)

option(smoc_BUILD_EXAMPLES "Build smoc examples" ON)

find_package(PythonInterp)

set(CMAKE_CXX_STANDARD 11)

if(NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

function(smoc_generate FILENAME TEMPLATE OUTPUT)
  get_filename_component(NAME ${FILENAME} NAME_WE)
  add_custom_command(
    COMMENT "Generating smoc for ${OUTPUT}"
    OUTPUT ${OUTPUT}
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/src/smoc.py ${FILENAME} -o ${OUTPUT} -t ${TEMPLATE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${CMAKE_SOURCE_DIR}/src/smoc.py ${FILENAME} ${TEMPLATE}
  )
  set_source_files_properties(${OUTPUT}
    PROPERTIES GENERATED TRUE)
endfunction()

#examples
if(smoc_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
