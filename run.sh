# Go to the build directory
cd build

# Generate the build filess
cmake ..

# Build the project
cmake --build .

echo

read -p "Press [Enter] to continue..."

clear

# Run the executable
./ddp_tictactoe 