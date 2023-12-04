cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME "FrangiTest")

project(${PROJECT_NAME} VERSION 0.0.0)

add_subdirectory(C:/JUCE juce)

juce_add_gui_app(${PROJECT_NAME}
        # ICON_BIG ...                  # ICON_* arguments specify a path to an image file to use as an icon
        # ICON_SMALL ...
        # DOCUMENT_EXTENSIONS ...       # Specify file extensions that should be associated with this app
        COMPANY_NAME "Frangitron"       # Specify the name of the app's author
        PRODUCT_NAME ${PROJECT_NAME})   # The name of the final executable, which can differ from the target name

target_sources(${PROJECT_NAME}
        PRIVATE
        src/Main.cpp
        src/MainComponent.cpp)

target_compile_definitions(${PROJECT_NAME}
        PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCER_ENABLE_GPL_MODE=1
        JUCE_DISPLAY_SPLASH_SCREEN=0
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_VERSION>")

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        # GuiAppData            # If we'd created a binary data target, we'd link to it here
        juce::juce_gui_extra
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
