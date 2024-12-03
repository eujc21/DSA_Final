# Load the debug and release variables
file(GLOB DATA_FILES "${CMAKE_CURRENT_LIST_DIR}/rapidcsv-*-data.cmake")

foreach(f ${DATA_FILES})
    include(${f})
endforeach()

# Create the targets for all the components
foreach(_COMPONENT ${rapidcsv_COMPONENT_NAMES} )
    if(NOT TARGET ${_COMPONENT})
        add_library(${_COMPONENT} INTERFACE IMPORTED)
        message(${rapidcsv_MESSAGE_MODE} "Conan: Component target declared '${_COMPONENT}'")
    endif()
endforeach()

if(NOT TARGET rapidcsv::rapidcsv)
    add_library(rapidcsv::rapidcsv INTERFACE IMPORTED)
    message(${rapidcsv_MESSAGE_MODE} "Conan: Target declared 'rapidcsv::rapidcsv'")
endif()
# Load the debug and release library finders
file(GLOB CONFIG_FILES "${CMAKE_CURRENT_LIST_DIR}/rapidcsv-Target-*.cmake")

foreach(f ${CONFIG_FILES})
    include(${f})
endforeach()