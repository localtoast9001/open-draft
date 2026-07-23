file(GLOB_RECURSE OPENDRAFT_LANG_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx"
)

if(NOT OPENDRAFT_LANG_SOURCES)
  # Keep the target buildable while source files are still being added.
  set(OPENDRAFT_LANG_STUB "${CMAKE_CURRENT_BINARY_DIR}/lang.stub.cpp")
  file(WRITE "${OPENDRAFT_LANG_STUB}" "namespace opendraft::lang {}\n")
  list(APPEND OPENDRAFT_LANG_SOURCES "${OPENDRAFT_LANG_STUB}")
endif()

add_library(opendraft_lang STATIC ${OPENDRAFT_LANG_SOURCES})

target_compile_options(opendraft_lang
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/Zi>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-g3>
)

target_include_directories(opendraft_lang
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../inc/pub/core
    ${CMAKE_CURRENT_SOURCE_DIR}/../../inc/pub/lang
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../inc/private/core
    ${CMAKE_CURRENT_SOURCE_DIR}/../../inc/private/lang
)

target_link_libraries(opendraft_lang PUBLIC opendraft_core)