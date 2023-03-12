# Root folder
cmake_minimum_required(VERSION 3.25)

project(MinecraftTool)
add_subdirectory(rapidjson)
add_subdirectory(JsonToObj)
add_subdirectory(MinecraftTool)

target_include_directories(MinecraftTool PUBLIC
	"${PROJECT_BINARY_DIR}" 
	"${JsonToObjIncludeDir}"
	)
	
install(TARGETS MinecraftTool DESTINATION bin)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")

set(CPACK_GENERATOR NSIS)
set(CPACK_NSIS_MODIFY_PATH ON)
include(CPack)