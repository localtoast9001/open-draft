file(GLOB_RECURSE OPENDRAFT_LANG_UT_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx"
)

add_executable(lang_ut
 ${OPENDRAFT_LANG_UT_SOURCES}
)

target_include_directories(lang_ut
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../inc/private/core
    ${CMAKE_CURRENT_SOURCE_DIR}/../../inc/private/lang
)

target_link_libraries(lang_ut
  PRIVATE
    testfx
    opendraft_core
    opendraft_lang
    opendraft_lang_tools
)

target_compile_options(lang_ut
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/Zi>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-g3>
)

target_link_options(lang_ut
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/DEBUG>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-g3>
)

set(OPEN_DRAFT_CPP_TESTCASES_PARSER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../testcases/parser")
set(OPEN_DRAFT_CPP_TESTCASES_PARSER_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../out/cpp/bin/testcases/parser")

add_custom_command(TARGET lang_ut POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory "${OPEN_DRAFT_CPP_TESTCASES_PARSER_OUTPUT_DIR}"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${OPEN_DRAFT_CPP_TESTCASES_PARSER_DIR}" "${OPEN_DRAFT_CPP_TESTCASES_PARSER_OUTPUT_DIR}"
  COMMENT "Copying parser testcases to output directory"
)
