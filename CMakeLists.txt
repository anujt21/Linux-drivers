cmake_minimum_required(VERSION 3.10)
project(LinuxDriver)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Determine if we're building a kernel module or user-space application
option(BUILD_KERNEL_MODULE "Build as a kernel module" ON)

if(BUILD_KERNEL_MODULE)
  # Kernel module build

  # Find kernel build directory
  execute_process(
        COMMAND uname -r
        OUTPUT_VARIABLE KERNEL_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
  set(KERNEL_BUILD_DIR "/lib/modules/${KERNEL_VERSION}/build")

  # Define the module name (based on your Makefile)
  set(MODULE_NAME "log_level")

  # Create custom commands to build the kernel module
  add_custom_target(modules ALL
        COMMAND ${CMAKE_MAKE_PROGRAM} -C ${KERNEL_BUILD_DIR} M=${CMAKE_CURRENT_SOURCE_DIR} modules
        COMMENT "Building kernel module ${MODULE_NAME}.ko"
        VERBATIM
    )

  # Create a custom command to clean module build files
  add_custom_target(clean_module
        COMMAND ${CMAKE_MAKE_PROGRAM} -C ${KERNEL_BUILD_DIR} M=${CMAKE_CURRENT_SOURCE_DIR} clean
        COMMENT "Cleaning kernel module build files"
        VERBATIM
    )

  # Create a Kbuild file for the kernel build system
  file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/Kbuild "obj-m := ${MODULE_NAME}.o\n")

  # Create an empty target to satisfy CMake
  add_custom_target(${PROJECT_NAME})

  # Install target for the kernel module
  install(
        CODE "execute_process(COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target modules)"
        CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_NAME}.ko ${CMAKE_INSTALL_PREFIX}/lib/modules)"
    )
else()
  # Regular user-space application build

  # Force C++ mode (for tools like clang)
  add_compile_options(
        -x c++
    )

  # Find all source files
  file(GLOB SOURCES
        ${CMAKE_SOURCE_DIR}/src/*.cpp
    )

  # Create executable
  add_executable(${PROJECT_NAME} ${SOURCES})

  # Install target
  install(TARGETS ${PROJECT_NAME} DESTINATION bin)
endif()

# Add custom target for make clean compatibility
add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
    DEPENDS clean_module
    COMMENT "Cleaning all build files"
    VERBATIM
)
