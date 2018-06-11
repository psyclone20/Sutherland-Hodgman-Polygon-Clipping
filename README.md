# Sutherland-Hodgman Polygon Clipping
An implementation of the [Sutherland–Hodgman algorithm](https://en.wikipedia.org/wiki/Sutherland%E2%80%93Hodgman_algorithm "Wikipedia") used for clipping polygons in C

# Input
The user must provide the following inputs:
* Top left and bottom right co-ordinates of the clipping window
* Co-ordinates of the vertices of the polygon

# Output
The portion of the polygon remaining after performing left, top, right and bottom clipping using the clipping window.