cmake_minimum_required(VERSION 3.17)
project(GUI_FOR_SETTINGS)

set(CMAKE_CXX_STANDARD 20)

add_executable(GUI_FOR_SETTINGS main.cpp data_settings.h data_settings.cpp)
target_link_libraries(GUI_FOR_SETTINGS  ${/usr/include/} -lopencv_core ${/usr/include/} -lopencv_highgui ${/usr/include/} -lopencv_videoio ${/usr/include/} -lopencv_imgcodecs)