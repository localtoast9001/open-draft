file (GLOB SOURCES "*.cpp")

add_library(xml STATIC ${SOURCES})

target_compile_options(xml
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/Zi>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-g3>
)

target_include_directories(xml
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../inc/private
)