# JsonToObj subdirectory
add_library(FileConverter FileConverter.cpp)
set(FileConverterIncludeDir "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)

target_include_directories(FileConverter PUBLIC
	"${JSONIncludeDir}" 
	)