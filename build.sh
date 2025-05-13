#!/bin/bash
# Exit on error
set -e

# Check for debug flag
if [ "$1" == "-d" ]; then
  BUILD_DIR="dbuild"
  DEBUG_FLAG="CONFIG_DEBUG=y"
  echo "Building in debug mode..."
else
  BUILD_DIR="build"
  DEBUG_FLAG=""
  echo "Building in release mode..."
fi

# Create build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
  mkdir -p "$BUILD_DIR"
fi

# Check for required environment variables
if [ -z "$ARCH" ]; then
  echo "WARNING: ARCH environment variable not set. Defaulting to arm64"
  export ARCH=arm64
fi

if [ -z "$CROSS_COMPILE" ]; then
  echo "WARNING: CROSS_COMPILE environment variable not set. Defaulting to aarch64-linux-gnu-"
  export CROSS_COMPILE=aarch64-linux-gnu-
fi

echo "Building for architecture: $ARCH"
echo "Using cross compiler: $CROSS_COMPILE"

# Generate build system and build the project
cd "$BUILD_DIR"
cmake ..
cmake --build . -- $DEBUG_FLAG

# Print success message
echo ""
echo "Build completed successfully!"
if [ "$1" == "-d" ]; then
  echo "Build type: Debug"
else
  echo "Build type: Release"
fi
echo "The kernel module (.ko file) can be found in the project directory."
