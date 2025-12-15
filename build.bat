@echo off

REM Create directories if they don't exist
if not exist build mkdir build
if not exist install mkdir install

REM Configure with install prefix
cmake -S . -B build -DCMAKE_INSTALL_PREFIX=./install

REM Build the project (Release configuration)
cmake --build build --config Release

REM Install to the install directory (Release configuration)
cmake --install build --config Release

echo.
echo Build complete! Executable is in the install/bin directory.
pause