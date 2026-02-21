cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(my_openplc_app)

# Include PLC logic files
file(GLOB_RECURSE app_sources src/*.c src/*.cpp)

# Add include paths
zephyr_include_directories(src/core src/core/lib)

target_sources(app PRIVATE ${app_sources})
