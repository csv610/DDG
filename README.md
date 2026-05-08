# Discrete Differential Geometry (DDG) Framework

This repository contains a framework for writing digital geometry processing (DGP) applications based on Discrete Exterior Calculus (DEC). It was originally developed for the SIGGRAPH 2013 course on Discrete Differential Geometry.

## Overview

The framework provides a practical interface for typical geometry operations on simplicial complexes (meshes). It includes a built-in viewer for real-time visualization and interaction with 3D models.

### Sub-projects

- **BaseCode**: The core library providing data structures for meshes (HalfEdge), linear algebra wrappers, and the basic DEC operators.
- **Connection**: Implementation of discrete connections on surface meshes.
- **Elasticity**: Physical simulation and deformation using elastic energy.
- **Fairing**: Mesh smoothing and fairing techniques.
- **Flatten**: Mesh parameterization and flattening algorithms.
- **Geodesics**: Computation of geodesic distances on surfaces.
- **Hot2**: Implementation of the "Heat Method" for geodesics.

## Prerequisites

To build and run the applications, you will need the following dependencies:

- **CMake** (version 3.10 or higher)
- **C++ Compiler** with C++20 support
- **OpenGL**
- **GLUT** (FreeGLUT recommended on Linux/Windows)
- **SuiteSparse** (including SPQR, CHOLMOD, UMFPACK)
- **BLAS/LAPACK** (e.g., OpenBLAS or the Accelerate framework on macOS)

### Installation on macOS

```bash
brew install suitesparse freeglut cmake
```

## Building the Project

The project uses CMake for the build system.

1. Create a build directory:
   ```bash
   mkdir build && cd build
   ```
2. Configure the project:
   ```bash
   cmake ..
   ```
3. Build the applications:
   ```bash
   make
   ```

This will generate executables for each sub-project and their corresponding tests in the `build` directory.

## Usage

Run any of the sub-project executables by providing an input mesh file (OBJ format):

```bash
./build/Geodesics ../testdata/armadillo.obj
```

### Viewer Controls

- **Left Click**: Rotate the camera.
- **Right Click**: Open the context menu.
- **Shift + Left Click**: Pick/unpick a vertex.
- **Space**: Run/pause the application logic.
- **w**: Save the current mesh to an OBJ file.
- **f**: Toggle wireframe mode.
- **Cmd/Ctrl + r**: Reload the input mesh.
- **- / =**: Decrease/increase the time step for simulations.

## Authors

Developed by:
- **Keenan Crane**
- **Fernando de Goes**
- **Mathieu Desbrun**
- **Peter Schröder**

Originally for the SIGGRAPH 2013 Course on Discrete Differential Geometry.

## License

This project is provided under a BSD-style license. See the `HOWTO` file for the full license text.
