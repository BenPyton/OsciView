# Copyright (c) 2023 Sebastian Pipping <sebastian@pipping.org>
# Licensed under the MIT license

cmake_minimum_required(VERSION 3.5)

project(OsciView VERSION 1.0.1)

if(WIN32)
    if(NOT DEFINED SFML_HOME)
        if(DEFINED ENV{SFML_HOME})
            set(SFML_HOME $ENV{SFML_HOME})
        else()
            message(FATAL_ERROR "SFML_HOME is not defined. Please, set it with -DSFML_HOME=path/to/sfml in cmake command, or add an environment variable in Windows, or set it from your IDE settings.")
        endif()
    endif()

    message(STATUS "Using SFML_HOME=${SFML_HOME}")
    set(SFML_DIR "${SFML_HOME}/lib/cmake/SFML")
endif()

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/modules/fft-real/ffft")
    find_package(Git)
    if(GIT_FOUND AND EXISTS "${CMAKE_SOURCE_DIR}/.git")
        # Project cloned from a git repo. We can initialize submodules with git.
        option(GIT_SUBMODULE "Check submodules during build" ON)
        if(GIT_SUBMODULE)
            message(STATUS "Updating git submodules.")
            execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                            RESULT_VARIABLE GIT_SUBMODULE_RESULT)
            if(NOT GIT_SUBMODULE_RESULT EQUAL "0")
                message(FATAL_ERROR "Git submodule update failed with result ${GIT_SUBMODULE_RESULT}.")
            endif()
        endif()
    else()
        # User needs to download manually.
        # TODO: Is there a way to download it automatically with FetchContent or ExternalProject? 
        message(FATAL_ERROR "The submodule fft-real was not found. Please download it from https://github.com/andywang0607/fft-real and place it in the \"modules\" folder.")
    endif()
endif()

set(SFML_STATIC_LIBRARIES FALSE)
find_package(SFML 2.5.1 COMPONENTS audio graphics REQUIRED CONFIG)

if(WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(COMPILER_ARCHITECTURE x64)
    else()
        set(COMPILER_ARCHITECTURE x86)
    endif()

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${COMPILER_ARCHITECTURE}/${CMAKE_BUILD_TYPE}")
endif()

add_executable(OsciView
    src/Core/Animation.cpp
    src/Core/Animation.h
    src/Core.h
    src/Core/Input.cpp
    src/Core/Input.h
    src/Core/Random.cpp
    src/Core/Random.h
    src/Core/Time.cpp
    src/Core/Time.h
    src/Core/Utils.cpp
    src/Core/Utils.h
    src/Core/Window.cpp
    src/Core/Window.h
    src/FreqView.cpp
    src/FreqView.h
    src/main.cpp
    src/Math/Matrix3.cpp
    src/Math/Matrix3.h
    src/Math/Matrix4.cpp
    src/Math/Matrix4.h
    src/Math/Vector2.cpp
    src/Math/Vector2.h
    src/Math/Vector3.cpp
    src/Math/Vector3.h
    src/OsciView.cpp
    src/OsciView.h
    src/SpectrumView.cpp
    src/SpectrumView.h
    src/StereoRecorder.cpp
    src/StereoRecorder.h
    src/UI/AbstractSlider.cpp
    src/UI/AbstractSlider.h
    src/UI/AbstractUI.cpp
    src/UI/AbstractUI.h
    src/UI/Button.cpp
    src/UI/Button.h
    src/UI/DialButton.cpp
    src/UI/DialButton.h
    src/UI/DraggableBox.cpp
    src/UI/DraggableBox.h
    src/UI.h
    src/UI/HorizontalLayout.cpp
    src/UI/HorizontalLayout.h
    src/UI/IconButton.cpp
    src/UI/IconButton.h
    src/UI/InputField.cpp
    src/UI/InputField.h
    src/UI/Label.cpp
    src/UI/Label.h
    src/UI/Layout.cpp
    src/UI/Layout.h
    src/UI/Scrollbar.cpp
    src/UI/Scrollbar.h
    src/UI/Toggle.cpp
    src/UI/Toggle.h
    src/UI/UIManager.cpp
    src/UI/UIManager.h
    src/UI/UIStyle.cpp
    src/UI/UIStyle.h
    src/UI/VerticalLayout.cpp
    src/UI/VerticalLayout.h
    src/UI/View.cpp
    src/UI/View.h
    src/WaveView.cpp
    src/WaveView.h
    src/FFTWrapper.cpp
    src/FFTWrapper.h
    src/Types.h
)

target_include_directories(OsciView
    PRIVATE
    "modules/fft-real"
)

target_link_libraries(OsciView
    PRIVATE
    sfml-graphics
    sfml-audio
)

if(WIN32)
    if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_link_options(OsciView PRIVATE "-mwindows")
    endif()

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(SFML_LIB_POSTFIX -d-2)
    else()
        set(SFML_LIB_POSTFIX -2)
    endif()

    get_filename_component(COMPILER_DIR ${CMAKE_CXX_COMPILER} DIRECTORY)
    set(DLLS_TO_COPY
        \"${COMPILER_DIR}/libstdc++-6.dll\"
        \"${SFML_HOME}/bin/openal32.dll\"
        \"${SFML_HOME}/bin/sfml-system${SFML_LIB_POSTFIX}.dll\"
        \"${SFML_HOME}/bin/sfml-window${SFML_LIB_POSTFIX}.dll\"
        \"${SFML_HOME}/bin/sfml-graphics${SFML_LIB_POSTFIX}.dll\"
        \"${SFML_HOME}/bin/sfml-audio${SFML_LIB_POSTFIX}.dll\"
    )

    add_custom_command(
        TARGET OsciView
        POST_BUILD
        # Multifile copy requires CMake >= 3.5
        COMMAND ${CMAKE_COMMAND} -E copy ${DLLS_TO_COPY} \"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}\"
        COMMENT "POST BUILD: Copying dlls in the output directory."
    )

    add_custom_command(
        TARGET OsciView
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory \"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data\"
        COMMAND ${CMAKE_COMMAND} -E copy_directory \"${CMAKE_SOURCE_DIR}/data/\" \"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data\"
        COMMENT "POST BUILD: Copying data folder in output directory."
    )
    
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_custom_command(
            TARGET OsciView
            POST_BUILD
            WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
            COMMAND ${CMAKE_COMMAND} -E make_directory \"${CMAKE_SOURCE_DIR}/packaged\"
            COMMAND ${CMAKE_COMMAND} -E tar \"cfv\" \"${CMAKE_SOURCE_DIR}/packaged/${PROJECT_NAME}-${PROJECT_VERSION}-${COMPILER_ARCHITECTURE}.zip\" --format=zip -- "."
            COMMENT "POST BUILD: Packaging the release."
        )
    endif()
endif()
