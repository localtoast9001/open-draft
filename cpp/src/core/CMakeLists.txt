file(GLOB_RECURSE OPENDRAFT_CORE_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx"
)

if(NOT OPENDRAFT_CORE_SOURCES)
  # Keep the target buildable while source files are still being added.
  set(OPENDRAFT_CORE_STUB "${CMAKE_CURRENT_BINARY_DIR}/core.stub.cpp")
  file(WRITE "${OPENDRAFT_CORE_STUB}" "namespace opendraft::core {}\n")
  list(APPEND OPENDRAFT_CORE_SOURCES "${OPENDRAFT_CORE_STUB}")
endif()

add_library(opendraft_core STATIC ${OPENDRAFT_CORE_SOURCES})

target_compile_options(opendraft_core
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/Zi>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-g3>
)

target_include_directories(opendraft_core
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../inc/pub/core
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../inc/private/core
)