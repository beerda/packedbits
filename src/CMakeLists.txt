set(HEADER_LIST
    "${packedbits_SOURCE_DIR}/include/common.h")

add_library(packedbits_lib INTERFACE)
target_sources(packedbits_lib INTERFACE "${HEADER_LIST}")
target_include_directories(packedbits_lib INTERFACE "${packedbits_SOURCE_DIR}/include/")
