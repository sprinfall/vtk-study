# vtk-study
Examples and notes for VTK.

## Build On Windows

### Install VTK

When config `CMAKE_INSTALL_PREFIX` for VTK, don't use Windows slash for the path. Otherwise the final installed VTKConfig.cmake will be invalid because of the slashes.
E.g., don't use "D:\lib\vtk_install", use "D:/lib/vtk_install" intead.

Add an environment variable `VTK_DIR` to the install dir of VTK. E.g.,
```
VTK_DIR = D:/lib/vtk_install
```
CMake `find_package(VTK)` needs this `VTK_DIR` to work.

