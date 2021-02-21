cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0060 NEW)
cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# include what you use
find_program(iwyu_path NAMES include-what-you-use iwyu)
if(iwyu_path)
    set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "${iwyu_path};-Xiwyu;--mapping_file=${CMAKE_SOURCE_DIR}/iwyu.imp")
endif()

file(READ "${CMAKE_CURRENT_SOURCE_DIR}/partgen.manifest" RAW_VERSION)
string(REGEX MATCH [0-9]+\\.[0-9]+\\.[0-9]+ PARTGEN_BASE_VERSION "${RAW_VERSION}")

project(partgen LANGUAGES CXX VERSION "${PARTGEN_BASE_VERSION}")
set(PARTGEN_VERSION_MAJOR "${partgen_VERSION_MAJOR}")
set(PARTGEN_VERSION_MINOR "${partgen_VERSION_MINOR}")
set(PARTGEN_VERSION_PATCH "${partgen_VERSION_PATCH}")
configure_file(include/partgen/version.h.in version.h)
message(STATUS "PARTGEN VERSION: ${PARTGEN_VERSION_MAJOR}.${PARTGEN_VERSION_MINOR}.${PARTGEN_VERSION_PATCH}")

include(FusionLibs)
message(STATUS "Fusion Settings:")
message(STATUS "  Includes: ${AD_FUSION_INCLUDES}")
message(STATUS "  Libraries: ${AD_FUSION_LIBS}")
message(STATUS "  Install dir: ${AD_FUSION_INSTALL_DIR}")

include(ClangFormat)
include(CTest)
include(FetchContent)

################################################################################
# Modules
################################################################################
add_subdirectory(addin)
add_subdirectory(src)
add_subdirectory(test)

################################################################################
# Custom targets
################################################################################
add_custom_target(uninstall COMMAND rm -rf "${AD_FUSION_INSTALL_DIR}")
