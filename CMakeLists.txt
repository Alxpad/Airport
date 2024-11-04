# Almost all CMake files should start with this
# You should always specify a range with the newest
# and oldest tested versions of CMake. This will ensure
# you pick up the best policies.
cmake_minimum_required(VERSION 3.15...3.30)

# This is your project statement. You should always list languages;
# Listing the version is nice here since it sets lots of useful variables
project("Aeropuerto")

# Add all the .cpp as the .h files to be compiled
# Use file(GLOB MY_SOURCES if there are a lot of files)
# Example:

# file(GLOB MY_SOURCES "src/*.cpp" "src/*.hpp" "src/*.h" "include/your-project/*.h" "include/your-project/*.hpp")

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

add_executable( ${PROJECT_NAME} ${SOURCES} ${HEADERS})

# It is not enough with this instruction. We have just indicated which files to includo, but not their location.
# The next step is to tell the compiler where these files are located.

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)

# Creating a library
# Is the same as creating an executable
# We use libraries whenever we need to add a .h and correspondent .cpp to the compiled executable
# Example:

# add_library("${PROJECT_NAME}_helper_lib" "helper_library/src/lib.cpp" "helper_library/include/helper_library/lib.hpp")

# Setting C++ Version
# Once created a executable or library, C++ version to be used must be set
# We do this using target_compile_features
# Example:

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
# VIP: Always use target_compile_features

# Adding 3rd party libraries
# CMake will visit the directories and execute their CMakeLists.txt
# Only works if that directory has a CMakeLists.txt
# Is a very good option to modularize the code
# Example:

# add_subdirectory("3rdparty/external_library1")
# Linking Libraries
# After adding the libraries, we want to make them availaable to our executable.
# We do this linking them
# the PRIVATE access specifier has no effect for executable targets, but when linking
# libraries to other libraries, we can enforce encapsulation preventing other components
# being made availabñe
# Example:

# target_link_libraries ("${PROJECT_NAME}"
# PRIVATE
# "${PROJECT_NAME}_helper_lib"
# external_library1
# extenal_library2
# )

# Now we can generate the build system and compile our program
# To get the list of supported systems, run cmake --help
# 
# Command to generate build system:
#   cmake -S . -B build -G "<Generator name>"
#
#   If you omit the -G flag, will use the default generator
#
#   -S --> Root where CMakeLists.txt is
#   -B --> Where to place the compiled data (out-of-source build) [Carpeta build]
#
#
#
# COMPILING
# Time to invoke the build system
# cmake --build build/ --config debug --target yourexe --parallel
#
# --build build/ --> Build directory where the config files where generated
# --config debug --> Compilation config. Multiple options available as Debug, Release, RelWithDebInfo...
# --target yourexe --> Target to be compiled. Can be an executable, library, or another object defined by CMake
# -- parallel --> Use parallel threads, speeding up the compilation depending on CPU cores available.s