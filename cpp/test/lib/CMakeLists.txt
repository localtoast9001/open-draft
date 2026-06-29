file(GLOB_RECURSE TESTFX_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx"
)

if(NOT TESTFX_SOURCES)
  # Keep the target buildable while source files are still being added.
  set(TESTFX_STUB "${CMAKE_CURRENT_BINARY_DIR}/testfx.stub.cpp")
  file(WRITE "${TESTFX_STUB}" "namespace testfx {}\n")
  list(APPEND TESTFX_SOURCES "${TESTFX_STUB}")
endif()

add_library(testfx STATIC ${TESTFX_SOURCES})

target_include_directories(testfx
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../inc/test
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../inc
)
