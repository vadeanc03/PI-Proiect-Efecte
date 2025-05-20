cmake_minimum_required(VERSION 3.14)
project(Proiect_PI_Special_Effects)

set(CMAKE_CXX_STANDARD 17)

# --- Find OpenCV
find_package(OpenCV REQUIRED)

# --- Include dir pentru header-e din src
include_directories(
        ${OpenCV_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/src
)

# --- Main executable
add_executable(Proiect_PI_Special_Effects
        main.cpp
        src/efecte.cpp
)
target_link_libraries(Proiect_PI_Special_Effects
        ${OpenCV_LIBS}
)

# --- Test suite executable
add_executable(test_suite
        tests/TestSuite.cpp
        src/efecte.cpp
)
target_link_libraries(test_suite
        ${OpenCV_LIBS}
)
