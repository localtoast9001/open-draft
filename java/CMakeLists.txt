cmake_minimum_required(VERSION 3.20)

project(open_draft_java VERSION 0.9.0 LANGUAGES Java)

find_package(Java REQUIRED)
include(UseJava)

set(open_draft_java_output_dir ${CMAKE_CURRENT_SOURCE_DIR}/../out/java)

add_custom_target(checkstyle
  COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/run-checkstyle.sh
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "Running Checkstyle (Sun style)"
)

file(MAKE_DIRECTORY ${open_draft_java_output_dir})

function(add_open_draft_package target_name package_name source_dir)
  file(GLOB_RECURSE package_sources CONFIGURE_DEPENDS "${source_dir}/*.java")

  if(package_sources)
    add_jar(${target_name}
      SOURCES ${package_sources}
      OUTPUT_NAME ${package_name}
      OUTPUT_DIR ${open_draft_java_output_dir}
    )
  else()
    message(STATUS "Skipping ${package_name}: no Java sources found in ${source_dir}")
  endif()
endfunction()

add_open_draft_package(
  opendraft_core
  io.github.localtoast9001.opendraft.core
  ${CMAKE_CURRENT_SOURCE_DIR}/src/io/github/localtoast9001/opendraft/core
)

add_open_draft_package(
  opendraft_lang
  io.github.localtoast9001.opendraft.lang
  ${CMAKE_CURRENT_SOURCE_DIR}/src/io/github/localtoast9001/opendraft/lang
)