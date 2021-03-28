# CMake generated Testfile for 
# Source directory: D:/zipper
# Build directory: D:/zipper/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(test_zipper_run "D:/zipper/build/Debug/Zipper-test.exe")
  set_tests_properties(test_zipper_run PROPERTIES  PASS_REGULAR_EXPRESSION "All tests passed" _BACKTRACE_TRIPLES "D:/zipper/CMakeLists.txt;373;add_test;D:/zipper/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(test_zipper_run "D:/zipper/build/Release/Zipper-test.exe")
  set_tests_properties(test_zipper_run PROPERTIES  PASS_REGULAR_EXPRESSION "All tests passed" _BACKTRACE_TRIPLES "D:/zipper/CMakeLists.txt;373;add_test;D:/zipper/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(test_zipper_run "D:/zipper/build/MinSizeRel/Zipper-test.exe")
  set_tests_properties(test_zipper_run PROPERTIES  PASS_REGULAR_EXPRESSION "All tests passed" _BACKTRACE_TRIPLES "D:/zipper/CMakeLists.txt;373;add_test;D:/zipper/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(test_zipper_run "D:/zipper/build/RelWithDebInfo/Zipper-test.exe")
  set_tests_properties(test_zipper_run PROPERTIES  PASS_REGULAR_EXPRESSION "All tests passed" _BACKTRACE_TRIPLES "D:/zipper/CMakeLists.txt;373;add_test;D:/zipper/CMakeLists.txt;0;")
else()
  add_test(test_zipper_run NOT_AVAILABLE)
endif()
