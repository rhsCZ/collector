#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Zipper" for configuration "Debug"
set_property(TARGET Zipper APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Zipper PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/Zipperd.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/Zipperd.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS Zipper )
list(APPEND _IMPORT_CHECK_FILES_FOR_Zipper "${_IMPORT_PREFIX}/lib/Zipperd.lib" "${_IMPORT_PREFIX}/bin/Zipperd.dll" )

# Import target "staticZipper" for configuration "Debug"
set_property(TARGET staticZipper APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(staticZipper PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C;CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/staticZipperd.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS staticZipper )
list(APPEND _IMPORT_CHECK_FILES_FOR_staticZipper "${_IMPORT_PREFIX}/lib/staticZipperd.lib" )

# Import target "Zipper-static" for configuration "Debug"
set_property(TARGET Zipper-static APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Zipper-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C;CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/Zipper-staticd.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Zipper-static )
list(APPEND _IMPORT_CHECK_FILES_FOR_Zipper-static "${_IMPORT_PREFIX}/lib/Zipper-staticd.lib" )

# Import target "Zipper-test" for configuration "Debug"
set_property(TARGET Zipper-test APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Zipper-test PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/Zipper-test.exe"
  )

list(APPEND _IMPORT_CHECK_TARGETS Zipper-test )
list(APPEND _IMPORT_CHECK_FILES_FOR_Zipper-test "${_IMPORT_PREFIX}/bin/Zipper-test.exe" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
