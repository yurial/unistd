file(GLOB_RECURSE UNISTD_SOURCES "*.cpp" "*.hpp")
add_library(unistd EXCLUDE_FROM_ALL ${UNISTD_SOURCES} )
