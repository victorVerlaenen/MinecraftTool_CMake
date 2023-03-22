# MinecraftTool subdirectory

add_executable(MinecraftTool MinecraftTool.cpp)
target_link_libraries(MinecraftTool PUBLIC JsonToObj)

target_include_directories(MinecraftTool PUBLIC
	"${JsonToObjIncludeDir}"
	)