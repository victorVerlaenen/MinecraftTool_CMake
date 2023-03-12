# JsonToObj subdirectory
add_library(JsonToObj JsonToObj.cpp)
set(JsonToObjIncludeDir "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)

target_include_directories(JsonToObj PUBLIC
	"${JSONIncludeDir}" 
	)