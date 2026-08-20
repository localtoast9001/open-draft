file(GLOB_RECURSE OPENDRAFT_LANG_TOOLS_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx"
)

if(NOT OPENDRAFT_LANG_TOOLS_SOURCES)
  # Keep the target buildable while source files are still being added.
  set(OPENDRAFT_LANG_TOOLS_STUB "${CMAKE_CURRENT_BINARY_DIR}/lang_tools.stub.cpp")
  file(WRITE "${OPENDRAFT_LANG_TOOLS_STUB}" "namespace opendraft::lang::tools {}\n")
  list(APPEND OPENDRAFT_LANG_TOOLS_SOURCES "${OPENDRAFT_LANG_TOOLS_STUB}")
endif()

add_library(opendraft_lang_tools STATIC ${OPENDRAFT_LANG_TOOLS_SOURCES})

target_compile_options(opendraft_lang_tools
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/Zi>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-g3>
)

target_include_directories(opendraft_lang_tools
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../inc/pub/core
    ${CMAKE_CURRENT_SOURCE_DIR}/../../inc/pub/lang
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../inc/private/core
    ${CMAKE_CURRENT_SOURCE_DIR}/../../inc/private/lang
)

target_link_libraries(opendraft_lang_tools PUBLIC opendraft_core opendraft_lang)