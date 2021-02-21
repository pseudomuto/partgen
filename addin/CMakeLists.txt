file(GLOB_RECURSE SOURCE_FILES LIST_DIRECTORIES true *.h *.cpp)
add_library(partgen SHARED ${SOURCE_FILES})
set_target_properties(partgen PROPERTIES PREFIX "")
target_clangformat_setup(partgen)

# fusion 360 linking
target_include_directories(partgen PRIVATE "${PROJECT_BINARY_DIR}")
target_include_directories(partgen PRIVATE "${AD_FUSION_INCLUDES}")
target_link_libraries(partgen PRIVATE libpartgen "${ADSK_CORE}" "${ADSK_FUSION}" "${ADSK_CAM}")

# Installation should go to addins dir for Fusion 360
install(TARGETS partgen DESTINATION "${AD_FUSION_INSTALL_DIR}")
install(FILES "${CMAKE_SOURCE_DIR}/partgen.manifest" DESTINATION "${AD_FUSION_INSTALL_DIR}")
install(DIRECTORY "${CMAKE_SOURCE_DIR}/resources/" DESTINATION "${AD_FUSION_INSTALL_DIR}/Resources")

