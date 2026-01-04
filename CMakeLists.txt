cmake_minimum_required(VERSION 3.26)
project(SDL3_Cpp_Demo LANGUAGES CXX)

# Richiede lo standard C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Cerca il pacchetto SDL3
find_package(SDL3 CONFIG REQUIRED)

# Aggiunge l'eseguibile
add_executable(SDL3_Cpp_Demo test.cpp)

# Collega le librerie di SDL3
target_link_libraries(SDL3_Cpp_Demo PRIVATE SDL3::SDL3)
