add_executable(lang_ut
  main.cpp
  source_reference_test.cpp
)

target_link_libraries(lang_ut
  PRIVATE
    testfx
    opendraft_core
    opendraft_lang
)
