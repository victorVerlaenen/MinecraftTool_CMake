# Root folder
cmake_minimum_required(VERSION 3.25)

project(MinecraftTool VERSION 1.0.0)
add_subdirectory("Libraries/rapidjson")
add_subdirectory("Libraries/FileConverter")
add_subdirectory("Libraries/JUCE")
add_subdirectory("MinecraftTool")
add_subdirectory("MinecraftToolGUI")
	
install(TARGETS "MinecraftTool" "MinecraftToolGUI" DESTINATION bin)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")

set(CPACK_GENERATOR NSIS)
set(CPACK_NSIS_MODIFY_PATH ON)
include(CPack)