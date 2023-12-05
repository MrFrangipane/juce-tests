cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_NAME "FrangiTest")

project(${PROJECT_NAME} VERSION 0.0.0)

add_subdirectory($ENV{JUCE_PATH} juce)

juce_add_gui_app(${PROJECT_NAME}
        COMPANY_NAME "Frangitron"
        PRODUCT_NAME ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_sources(${PROJECT_NAME}
        PRIVATE
        src/Main.cpp
        src/MainComponent.cpp)

target_compile_definitions(${PROJECT_NAME}
        PRIVATE
        JUCER_ENABLE_GPL_MODE=1
        JUCE_DISPLAY_SPLASH_SCREEN=0
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_VERSION>")

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        juce::juce_audio_utils
        juce::juce_gui_extra
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
