# CISP_400_Mandelbrot_Set

An interactive visualization of the Mandelbrot Set using C++ and SFML graphics library.

## Description

This project creates a visual representation of the Mandelbrot Set, one of the most famous fractals in mathematics. The program allows users to explore the fascinating mathematical object through an interactive interface where they can zoom in and out to discover the infinite complexity of the set.

### What is the Mandelbrot Set?

The Mandelbrot Set is a mathematical set of points in the complex plane, the boundary of which forms a fractal. Named after mathematician Benoit Mandelbrot, it is one of the most famous examples of mathematical visualization and demonstrates how complex and beautiful patterns can emerge from simple mathematical rules.

## Features

- Real-time rendering of the Mandelbrot Set
- Interactive zoom functionality
- Mouse-controlled navigation
- Dynamic color visualization
- Resolution scaling for optimal performance

## Controls

- **Left Click**: Zoom in at the clicked position
- **Right Click**: Zoom out at the clicked position
- **Mouse Movement**: Updates the current coordinates
- **ESC**: Exit the application

## Prerequisites

To build and run this project, you need:

- C++ compiler with C++17 support
- SFML 2.x (Simple and Fast Multimedia Library)
- Make build system
- Arial font file (arial.ttf)

### System Requirements

The application automatically scales to your desktop resolution (at 50% for optimal performance).

## Building the Project

1. Ensure you have SFML installed. On macOS with Homebrew:
   ```bash
   brew install sfml@2
   ```

2. Clone the repository:
   ```bash
   git clone [repository-url]
   cd CISP_400_Mandelbrot_Set
   ```

3. Build the project using make:
   ```bash
   make
   ```

4. Run the application:
   ```bash
   make run
   ```

## Project Structure

- `main.cpp`: Entry point and main application loop
- `ComplexPlane.h/cpp`: Handles the mathematical calculations and rendering
- `makefile`: Build configuration

## Authors

- Christopher Planow
- Ali Chenari

## Technical Details

- Written in C++17
- Uses SFML for graphics rendering
- Implements complex number mathematics for set calculation
- Dynamic resolution scaling for performance optimization

## Troubleshooting

If you encounter any issues:

1. Ensure SFML is properly installed and linked
2. Verify that arial.ttf is present in the project directory
3. Check if your system meets the minimum requirements
4. Make sure all dependencies are correctly installed
