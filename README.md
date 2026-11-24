# Lab 11 – Multiprocessing Mandelbrot Movie

Author: Brody Hyland
Course: CPE-2600 Systems Programming

# Program Overview

This project uses multiple child processes to generate a 50-frame Mandelbrot zoom movie. The number of child processes is specified by the user through the command line using the getopt() function.

# Compilation

Compile both programs using the Makefile:

make

To remove compiled programs and generated files:

make clean

# Running the Program

Specify the number of child processes using the -n option.

# Example:

./mandelmovie -n 5