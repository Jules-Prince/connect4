#!/bin/bash

# Exit on error
set -e

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Build the project
cmake ..
make

# Run the tests
./connect4_test

# Generate coverage data
lcov --capture --directory . --output-file coverage.info --ignore-errors inconsistent,mismatch

# Remove coverage data for system headers, test files, and plog
lcov --remove coverage.info '/usr/*' '*/tests/*' '*/googletest/*' '*/build/_deps/plog-src/include/plog/*' --output-file coverage.info --ignore-errors inconsistent,mismatch

# Generate HTML report
genhtml coverage.info --output-directory coverage_report

echo "Coverage report generated in build/coverage_report/index.html"