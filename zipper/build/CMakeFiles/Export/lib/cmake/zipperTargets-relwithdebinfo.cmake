#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Zipper" for configuration "RelWithDebInfo"
set_property(TARGET Zipper APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(Zipper PROPERTIES
  IMPORTED_IMPLIB_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/Zipper.lib"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/bin/Zipper.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS Zipper )
list(APPEND _IMPORT_CHECK_FILES_FOR_Zipper "${_IMPORT_PREFIX}/lib/Zipper.lib" "${_IMPORT_PREFIX}/bin/Zipper.dll" )

# Import target "staticZipper" for configuration "RelWithDebInfo"
set_property(TARGET staticZipper APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(staticZipper PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "C;CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/staticZipper.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS staticZipper )
list(APPEND _IMPORT_CHECK_FILES_FOR_staticZipper "${_IMPORT_PREFIX}/lib/staticZipper.lib" )

# Import target "Zipper-static" for configuration "RelWithDebInfo"
set_property(TARGET Zipper-static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(Zipper-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "C;CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/Zipper-static.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Zipper-static )
list(APPEND _IMPORT_CHECK_FILES_FOR_Zipper-static "${_IMPORT_PREFIX}/lib/Zipper-static.lib" )

# Import target "Zipper-test" for configuration "RelWithDebInfo"
set_property(TARGET Zipper-test APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(Zipper-test PROPERTIES
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/bin/Zipper-test.exe"
  )

list(APPEND _IMPORT_CHECK_TARGETS Zipper-test )
list(APPEND _IMPORT_CHECK_FILES_FOR_Zipper-test "${_IMPORT_PREFIX}/bin/Zipper-test.exe" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
