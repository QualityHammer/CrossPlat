add_library(utils INTERFACE)
target_sources(utils
    INTERFACE
    utils/stb_image.h
)
target_include_directories(utils
    INTERFACE
    "${PROJECT_SOURCE_DIR}/dependencies/utils"
)
