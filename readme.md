# Platonic Solids
* geometry array are sorted to match indices across duals (octa's points[0] is along the the cube's face[0] normal), so, an object's face normals correlate to vertex data from the object's dual
* one vertex aligned along +X, if possible another along +Y, then +Z
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