########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(rapidcsv_COMPONENT_NAMES "")
if(DEFINED rapidcsv_FIND_DEPENDENCY_NAMES)
  list(APPEND rapidcsv_FIND_DEPENDENCY_NAMES )
  list(REMOVE_DUPLICATES rapidcsv_FIND_DEPENDENCY_NAMES)
else()
  set(rapidcsv_FIND_DEPENDENCY_NAMES )
endif()

########### VARIABLES #######################################################################
#############################################################################################
set(rapidcsv_PACKAGE_FOLDER_RELEASE "/home/ejoya/.conan2/p/rapid60423a35d5620/p")
set(rapidcsv_BUILD_MODULES_PATHS_RELEASE )


set(rapidcsv_INCLUDE_DIRS_RELEASE "${rapidcsv_PACKAGE_FOLDER_RELEASE}/include")
set(rapidcsv_RES_DIRS_RELEASE )
set(rapidcsv_DEFINITIONS_RELEASE )
set(rapidcsv_SHARED_LINK_FLAGS_RELEASE )
set(rapidcsv_EXE_LINK_FLAGS_RELEASE )
set(rapidcsv_OBJECTS_RELEASE )
set(rapidcsv_COMPILE_DEFINITIONS_RELEASE )
set(rapidcsv_COMPILE_OPTIONS_C_RELEASE )
set(rapidcsv_COMPILE_OPTIONS_CXX_RELEASE )
set(rapidcsv_LIB_DIRS_RELEASE )
set(rapidcsv_BIN_DIRS_RELEASE )
set(rapidcsv_LIBRARY_TYPE_RELEASE UNKNOWN)
set(rapidcsv_IS_HOST_WINDOWS_RELEASE 0)
set(rapidcsv_LIBS_RELEASE )
set(rapidcsv_SYSTEM_LIBS_RELEASE )
set(rapidcsv_FRAMEWORK_DIRS_RELEASE )
set(rapidcsv_FRAMEWORKS_RELEASE )
set(rapidcsv_BUILD_DIRS_RELEASE )
set(rapidcsv_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(rapidcsv_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${rapidcsv_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${rapidcsv_COMPILE_OPTIONS_C_RELEASE}>")
set(rapidcsv_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${rapidcsv_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${rapidcsv_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${rapidcsv_EXE_LINK_FLAGS_RELEASE}>")


set(rapidcsv_COMPONENTS_RELEASE )