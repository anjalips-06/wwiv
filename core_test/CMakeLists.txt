include_directories(../deps/googletest/googletest/include)
include_directories(..)

set(fixture_sources
  file_helper.cpp 
)

set(test_sources
  clock_test.cpp
  crc32_test.cpp
  command_line_test.cpp
  datetime_test.cpp
  datafile_test.cpp
  fake_clock_test.cpp
  findfiles_test.cpp
  file_test.cpp
  inifile_test.cpp
  log_test.cpp
  md5_test.cpp
  os_test.cpp
  scope_exit_test.cpp
  semaphore_file_test.cpp
  stl_test.cpp
  strings_test.cpp
  textfile_test.cpp
  transaction_test.cpp
)

if(UNIX) 
  add_definitions ("-Wall")
endif()

add_library(core_fixtures ${fixture_sources}) 

target_link_libraries(core_fixtures core)
if(NOT UNIX)
  list(APPEND test_sources core_test_main.cpp)
endif()
add_executable(core_tests ${test_sources})

if(UNIX)
  target_link_libraries(core_tests core_fixtures core gtest_main)
else()
  target_link_libraries(core_tests core_fixtures core gtest)
endif()

add_test(core_tests core_tests)
