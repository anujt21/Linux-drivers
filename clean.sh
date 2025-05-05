#!/bin/bash

# clean.sh - Script to clean build folders and remove compiled kernel modules
# Usage: ./clean.sh

set -e # Exit immediately if a command exits with a non-zero status

echo "=== Starting cleanup process ==="

# Remove build folders
echo "Removing build directories..."
if [ -d "build" ]; then
  rm -rf build
  echo "✓ Removed 'build' directory"
fi

# Find and remove any other build directories
find . -type d -name "build*" -exec rm -rf {} \; 2>/dev/null || true
echo "✓ Removed any additional build directories"

# Clean CMake projects
echo "Cleaning CMake projects..."
if [ -f "CMakeCache.txt" ]; then
  cmake --build . --target clean
  rm -f CMakeCache.txt
  echo "✓ Cleaned CMake project"
fi

# Remove compiled kernel modules
echo "Removing kernel modules..."
find . -name "*.ko" -exec rm -f {} \;
echo "✓ Removed all compiled kernel modules (.ko files)"

# Remove other common build artifacts
echo "Removing other build artifacts..."
find . -name "*.o" -exec rm -f {} \;
find . -name "*.mod" -exec rm -f {} \;
find . -name "*.mod.c" -exec rm -f {} \;
find . -name "*.cmd" -exec rm -f {} \;
find . -name "Module.symvers" -exec rm -f {} \;
find . -name "modules.order" -exec rm -f {} \;
echo "✓ Removed all object files and kernel module artifacts"

echo "=== Cleanup complete! ==="
