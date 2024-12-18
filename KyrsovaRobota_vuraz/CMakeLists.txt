cmake_minimum_required(VERSION 3.10)
project(KyrsovaRobota_vuraz LANGUAGES CXX)

# Встановити стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")


# Указати, що ми створюємо спільну бібліотеку
add_library(Kyrsova SHARED Kyrsova.cpp)

# Оптимізації та видимість
if(CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_options(Kyrsova PRIVATE -fvisibility=hidden)
endif()

# Якщо потрібно додати інші флаги компіляції, зробіть це тут
if(MSVC)
    target_compile_options(Kyrsova PRIVATE /W4)
else()
    target_compile_options(Kyrsova PRIVATE -Wall -Wextra -pedantic)
endif()

# Встановлення бібліотеки
install(TARGETS Kyrsova DESTINATION lib)
