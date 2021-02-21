file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/partgen/*.h")
file(GLOB_RECURSE SOURCE_FILES LIST_DIRECTORIES true *.h *.cpp)

add_library(libpartgen STATIC ${SOURCE_FILES})
set_target_properties(libpartgen PROPERTIES PREFIX "")
target_clangformat_setup(libpartgen ${HEADER_LIST})

target_include_directories(libpartgen PUBLIC ../include)
target_include_directories(libpartgen PRIVATE "${PROJECT_BINARY_DIR}")

install(TARGETS libpartgen DESTINATION "${AD_FUSION_INSTALL_DIR}")
