# TODO: make this cross platform?
set(AD_FUSION_DIR "$ENV{HOME}/Library/Application\ Support/Autodesk/Autodesk\ Fusion\ 360/API")
set(AD_FUSION_INCLUDES "${AD_FUSION_DIR}/CPP/include")
set(AD_FUSION_LIBS "${AD_FUSION_DIR}/CPP/lib")
set(AD_FUSION_INSTALL_DIR "${AD_FUSION_DIR}/AddIns/${CMAKE_PROJECT_NAME}")

find_library(ADSK_CORE core.dylib PATHS "${AD_FUSION_LIBS}/")
find_library(ADSK_FUSION fusion.dylib PATHS "${AD_FUSION_LIBS}/")
find_library(ADSK_CAM cam.dylib PATHS "${AD_FUSION_LIBS}/")
