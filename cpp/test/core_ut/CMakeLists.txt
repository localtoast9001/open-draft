file(GLOB_RECURSE OPENDRAFT_CORE_UT_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx"
)

add_executable(core_ut
 ${OPENDRAFT_CORE_UT_SOURCES}
)

target_include_directories(core_ut
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../inc/private/core
)

target_link_libraries(core_ut
  PRIVATE
    testfx
    opendraft_core
)

target_compile_options(core_ut
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/Zi>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-g3>
)

target_link_options(core_ut
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/DEBUG>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-g3>
)

