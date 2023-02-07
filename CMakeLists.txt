# Copyright (c) 2023 Sebastian Pipping <sebastian@pipping.org>
# Licensed under the MIT license

cmake_minimum_required(VERSION 3.6)
# CMake features used that need more than CMake 3.0:
# - pkg_check_modules([..] IMPORTED_TARGET [..]) needs >=3.6

project(OsciView VERSION 1.0.0)

include(FindPkgConfig)

pkg_check_modules(SFML sfml-all REQUIRED IMPORTED_TARGET)

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
)

target_link_libraries(OsciView
    PUBLIC
    PkgConfig::SFML
)
