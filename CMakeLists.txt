cmake_minimum_required(VERSION 3.14)
project(Proiect_PI_Special_Effects)

set(CMAKE_CXX_STANDARD 17)

# --- Find OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Proiect_PI_Special_Effects
        main.cpp
        src/efecte.cpp
        src/efecte.h
)

target_link_libraries(Proiect_PI_Special_Effects ${OpenCV_LIBS})
