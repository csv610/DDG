# Discrete Differential Geometry (DDG) Framework

**Original Research & Framework by:**
**Keenan Crane, Fernando de Goes, Mathieu Desbrun, and Peter Schröder**
*(Originally developed for the SIGGRAPH 2013 Course on Discrete Differential Geometry)*

---

This repository contains the digital geometry processing (DGP) framework based on Discrete Exterior Calculus (DEC) as presented in the seminal SIGGRAPH 2013 course. All core algorithms, mathematical foundations, and the original DEC library implementation are the work of the researchers credited above.

## Overview

The framework provides a practical interface for typical geometry operations on simplicial complexes (meshes). It includes a built-in viewer for real-time visualization and interaction with 3D models.

### Research Modules

- **BaseCode**: Core DEC operators and mesh data structures.
- **Connection**: Discrete connections on surface meshes.
- **Elasticity**: Physical simulation via elastic energy.
- **Fairing**: Mesh smoothing and fairing.
- **Flatten**: Mesh parameterization and flattening.
- **Geodesics**: Computation of geodesic distances.
- **Hot2**: Heat Method for geodesics.

## Maintenance & Engineering Enhancements

To ensure the continued utility of this foundational research codebase in modern environments, the following **engineering-only** updates have been applied:

- **Modern Build Orchestration**: Replaced the original 2013 `Makefile` system with a unified `CMakeLists.txt` to support modern compilers and automated dependency discovery (SuiteSparse, OpenGL, GLUT).
- **Standards Update**: Minimal refactoring to support **C++20** and resolve deprecation warnings in modern GL/C++ environments.
- **Automated Validation**: Added a unit testing suite (`tests/`) to verify that the implementation of the researchers' algorithms remains correct across different platforms and compiler versions.
- **Dependency Management**: Streamlined linking with modern versions of SuiteSparse and the macOS Accelerate framework.

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

## License

This project is provided under a BSD-style license. All original research and code remain the intellectual property of the original authors. See the `HOWTO` file for the full license text.
