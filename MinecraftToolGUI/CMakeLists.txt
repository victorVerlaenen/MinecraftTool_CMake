# MinecraftToolGUI subdirectory

# Set the source files for the project
set(SOURCES
    Main.cpp
    MainComponent.h
    MainComponent.cpp
)

# Add an executable target for the project
juce_add_gui_app(MinecraftToolGUI
    PRODUCT_NAME "MinecraftToolGUI"
    VERSION "${PROJECT_VERSION}"
    COMPANY_NAME "VictorCorp"
    DOCUMENT_EXTENSIONS "bestext"
    DOCUMENT_NAMES "My Document"
    DOCUMENT_DESCRIPTIONS "My Document Description"
)

juce_generate_juce_header(MinecraftToolGUI)

target_sources(MinecraftToolGUI PRIVATE ${SOURCES} "TableModel.h" "TableModel.cpp" "NamedVector3.h" "NamedVector3.cpp")

# Link against the JUCE module
target_link_libraries(MinecraftToolGUI
    PRIVATE
        # GuiAppData            # If we'd created a binary data target, we'd link to it here
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
		FileConverter
)

target_include_directories(MinecraftToolGUI PUBLIC
	"${FileConverterIncludeDir}"
	)
