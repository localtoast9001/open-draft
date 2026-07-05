file(GLOB_RECURSE OPENDRAFT_LANG_UT_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx"
)

add_executable(lang_ut
 ${OPENDRAFT_LANG_UT_SOURCES}
)

target_link_libraries(lang_ut
  PRIVATE
    testfx
    opendraft_core
    opendraft_lang
)
