cmake_minimum_required(VERSION 3.10)
project(KernelModule C)

# Enable compile_commands.json generation
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C standard to use (likely C11 for kernel modules)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set module name to match your actual module name
set(MODULE_NAME "kernel_module")

# Check for required environment variables
if(NOT DEFINED ENV{ARCH})
  message(FATAL_ERROR "ARCH environment variable not set")
endif()

if(NOT DEFINED ENV{CROSS_COMPILE})
  message(FATAL_ERROR "CROSS_COMPILE environment variable not set")
endif()

# Print the current configuration
message(STATUS "Building for architecture: $ENV{ARCH}")
message(STATUS "Using cross compiler: $ENV{CROSS_COMPILE}")

# Kernel source directory
if(NOT DEFINED ENV{KDIR})
  set(KERNEL_DIR "$ENV{HOME}/linux")
else()
  set(KERNEL_DIR "$ENV{KDIR}")
endif()

# Define source and include directories
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Create a custom target for building the kernel module
add_custom_target(modules ALL
    COMMAND ${CMAKE_MAKE_PROGRAM} -C ${KERNEL_DIR} M=${CMAKE_CURRENT_SOURCE_DIR} modules
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Building kernel module ${MODULE_NAME}"
    VERBATIM
)

# Create a custom target for cleaning
add_custom_target(clean_module
    COMMAND ${CMAKE_MAKE_PROGRAM} -C ${KERNEL_DIR} M=${CMAKE_CURRENT_SOURCE_DIR} clean
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Cleaning kernel module build files"
    VERBATIM
)

# Install target
install(CODE "execute_process(COMMAND ${CMAKE_MAKE_PROGRAM} -C ${KERNEL_DIR} M=${CMAKE_CURRENT_SOURCE_DIR} modules_install)")

# In kernel module development, the source file needs to be in a specific location for the build system
# Copy the source file from src/ to the project root during the configuration
configure_file(
    "${SOURCE_DIR}/${MODULE_NAME}.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_NAME}.c"
    COPYONLY
)

# Force C language for all source files
file(GLOB C_FILES "${SOURCE_DIR}/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
foreach(C_FILE ${C_FILES})
  set_source_files_properties(${C_FILE} PROPERTIES LANGUAGE C)
endforeach()

# Create a Kbuild file that explicitly lists your source file
file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/Kbuild" "obj-m := ${MODULE_NAME}.o\n")

# Include directories for the kernel module
if(EXISTS "${INCLUDE_DIR}")
  file(APPEND "${CMAKE_CURRENT_SOURCE_DIR}/Kbuild" "ccflags-y := -I\$(src)/include\n")
endif()
