file(GLOB_RECURSE OPENDRAFT_ODLANG2XML_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx"
)

add_executable(odlang2xml ${OPENDRAFT_ODLANG2XML_SOURCES})

target_include_directories(odlang2xml
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../inc/private/core
    ${CMAKE_CURRENT_SOURCE_DIR}/../../inc/private/lang
)

target_link_libraries(odlang2xml
  PRIVATE
    opendraft_lang_tools
)

if(MSVC)
  target_compile_options(odlang2xml PRIVATE /Zi)
else()
  target_compile_options(odlang2xml PRIVATE -g3)
endif()
