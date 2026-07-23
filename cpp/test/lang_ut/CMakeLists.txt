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
