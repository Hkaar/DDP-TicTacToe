#!/bin/bash

# Create directories if they don't exist
mkdir -p build
mkdir -p install

# Configure with install prefix
cmake -S . -B build -DCMAKE_INSTALL_PREFIX=./install

# Build the project
cmake --build build

# Install to the install directory
cmake --install build

echo
read -p "Press [Enter] to continue..."
clear
