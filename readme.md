# Platonic Solids

`platonic.h` all the geometry

`platonic.c` OpenGL draw calls

![sample](https://raw.github.com/robbykraft/Platonic/master/bin/sample.gif)

* point, line, face geometry, dihedral angle, midradius, inradius, side length, volume
* polyhedra are aligned according to their duals (each face lies along its dual's point)
    * the array indices are aligned, a face index is its dual's point index
    * (this means an object's point data is its dual's face normal data)
* the triangle solids- at least one vertex lies along +X axis, and if possible another along +Y
* hexahedron and dodecahedron are face-aligned along +X (since they are aligned to their duals)
* each polyhedra is centered at origin
* each polyhedra's circumradius is 1.0 (center to point)
* clockwise winding
* only uses gl_triangles (OpenGL ES compatible)

![sample](https://raw.github.com/robbykraft/Platonic/master/bin/midradius.gif)

*example: scale by consecutive midradii*

# try it out
* example app is cross-platform Mac, Linux, Windows
* type `make` then `make run`

`input`

* `1` - `5` select between: tetra, octa, hexa, icosa, dodeca
* `SPACE BAR` toggle faces/lines/points
* `D` superimpose polyhedra's dual

# license
MIT
