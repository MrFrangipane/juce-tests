cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_NAME "FrangiTest")

project(${PROJECT_NAME} VERSION 0.0.0)

# BTrack
add_subdirectory(3rd-party/libsamplerate libsamplerate)
add_subdirectory(3rd-party/BTrack btrack)
include_directories(3rd-party/libsamplerate/include)
include_directories(3rd-party/libsamplerate/src)
include_directories(3rd-party/BTrack/libs/kiss_fft130)
include_directories(3rd-party/BTrack/src)
add_library(kiss_fft
        3rd-party/BTrack/libs/kiss_fft130/_kiss_fft_guts.h
        3rd-party/BTrack/libs/kiss_fft130/kiss_fft.c
        3rd-party/BTrack/libs/kiss_fft130/kiss_fft.h
        3rd-party/BTrack/libs/kiss_fft130/kissfft.hh
)
add_library(libsamplerate
        3rd-party/libsamplerate/src/common.h
        3rd-party/libsamplerate/src/fastest_coeffs.h
        3rd-party/libsamplerate/src/high_qual_coeffs.h
        3rd-party/libsamplerate/src/mid_qual_coeffs.h
        3rd-party/libsamplerate/src/samplerate.c
        3rd-party/libsamplerate/src/src_linear.c
        3rd-party/libsamplerate/src/src_sinc.c
        3rd-party/libsamplerate/src/src_zoh.c
        3rd-party/libsamplerate/include/samplerate.h
)

# JUCE
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
        libsamplerate
        kiss_fft
        BTrack
        juce::juce_audio_utils
        juce::juce_gui_extra
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
