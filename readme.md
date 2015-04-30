# Platonic Solids
* polyhedra are aligned according to their duals
* geometry data arrays are sorted to match indices across duals (octa's 2nd point in the array corresponds to cube's 2nd face in its array), so, an object's face normals are its dual's vertices.
* one vertex is aligned along +X, if possible another along +Y
* except hexahedron and dodecahedron, since they are aligned to their duals (octa and icosa) they are face-aligned along +X
* additional triangle-only face arrays (OpenGL ES) for hexahedron and dodecahedron
* clockwise winding
* radius 1.0
* centered at origin

![sample](https://raw.github.com/robbykraft/Platonic/master/sample.gif)

# try it out
* type `make` then `./world`
* cross-platform Mac, Linux, Windows

# input
* `1`:tetra, `2`:octa, `3`:hexa, `4`:icosa, `5`:dodeca
* `SPACE BAR` toggle faces/lines/points
* mouse rotate
* `+` `-` zoom in/out

# license
MIT