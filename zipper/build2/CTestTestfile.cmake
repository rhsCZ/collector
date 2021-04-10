# CMake generated Testfile for 
# Source directory: D:/gdrive/github/collector/zipper
# Build directory: D:/gdrive/github/collector/zipper/build2
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(test_zipper_run "D:/gdrive/github/collector/zipper/build2/Debug/Zipper-test.exe")
  set_tests_properties(test_zipper_run PROPERTIES  PASS_REGULAR_EXPRESSION "All tests passed" _BACKTRACE_TRIPLES "D:/gdrive/github/collector/zipper/CMakeLists.txt;373;add_test;D:/gdrive/github/collector/zipper/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(test_zipper_run "D:/gdrive/github/collector/zipper/build2/Release/Zipper-test.exe")
  set_tests_properties(test_zipper_run PROPERTIES  PASS_REGULAR_EXPRESSION "All tests passed" _BACKTRACE_TRIPLES "D:/gdrive/github/collector/zipper/CMakeLists.txt;373;add_test;D:/gdrive/github/collector/zipper/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(test_zipper_run "D:/gdrive/github/collector/zipper/build2/MinSizeRel/Zipper-test.exe")
  set_tests_properties(test_zipper_run PROPERTIES  PASS_REGULAR_EXPRESSION "All tests passed" _BACKTRACE_TRIPLES "D:/gdrive/github/collector/zipper/CMakeLists.txt;373;add_test;D:/gdrive/github/collector/zipper/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(test_zipper_run "D:/gdrive/github/collector/zipper/build2/RelWithDebInfo/Zipper-test.exe")
  set_tests_properties(test_zipper_run PROPERTIES  PASS_REGULAR_EXPRESSION "All tests passed" _BACKTRACE_TRIPLES "D:/gdrive/github/collector/zipper/CMakeLists.txt;373;add_test;D:/gdrive/github/collector/zipper/CMakeLists.txt;0;")
else()
  add_test(test_zipper_run NOT_AVAILABLE)
endif()
