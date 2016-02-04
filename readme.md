# Platonic Solids

`platonic.h` raw geometry data

`platonic.c` OpenGL rendering

![sample](https://raw.github.com/robbykraft/Platonic/master/bin/sample.gif)

# features
* point, line, face geometry, dihedral angle, midradius, inradius, side length, volume
* polyhedra are aligned according to their duals
    * this means each face lies along its dual's point
    * even the indices are aligned, a face index is its dual's point index
    * this means an object's face normal data is its dual's point data
* at least one vertex lies along +X axis, and if possible another along +Y
    * except hexahedron and dodecahedron, since they are aligned to their duals (they are face-aligned along +X)
* each polyhedra is centered at origin
* each polyhedra's circumradius is 1.0 (center to point)
* clockwise winding
* OpenGL ES compatible (triangles only)

![sample](https://raw.github.com/robbykraft/Platonic/master/bin/midradius.gif)

*example: scale involving midradius*

# try it out
* example app is cross-platform Mac, Linux, Windows
* type `make` then `make run`

# input
* `1` - `5` select between: tetra, octa, hexa, icosa, dodeca
* `SPACE BAR` toggle faces/lines/points
* `D` superimpose polyhedra's dual

# license
MIT