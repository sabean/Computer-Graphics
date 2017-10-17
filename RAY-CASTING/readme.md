# Ray caster

comparing different illumination and shading options using the raster graphics pipeline (OpenGL) and ray caster

## Set up and implementation

### Loading:
An arbitrary triangular mesh in OBJ format of bunny is loaded and it is stored as a (triangular) polygon soup.

### Set-up:
Given a 3D Cartesian coordinate system, the viewpoint is given as v = (0, 0, −2) and thescreen is given by the square with corners s 0 = (−1, −1, 0), s 1 = (−1, 1, 0), s 2 = (1, 1, 0), and s 3 = (1, −1, 0). Assuming perspective projection and range of sight 12, place three (not too small) spheres such that all three spheres are completely inside the view frustum and such that they partially occlude each other when looking at them from the viewpoint.

### Ray intersection:
A ray is sent from the viewpoint through the center of each pixel of the screen and compute its first intersection with the triangular mesh (if any). A ray-triangle intersection is performed.

### Returning colors:
In case the ray-mesh intersection did not deliver any intersection point, the respective pixel shall be assigned RGB color (0, 0, 0). Otherwise, if (x, y, z) are the coordinates of 6+y/10−z the intersection point, then RGB color ( 6+x/12 , 12 , 10 ) shall be assigned to the pixel. 

### Anti-aliasing:
A 2 × 2 subpixel supersampling anti-aliasing to improve the quality of result is applied.

### Shading
For the OpenGL rendering the built-in Gouraud shading is used, while for the ray casting rendering Phong shading is implemented.

## Opengl

### OpenGL rendering:
A sphere is rendered in OpenGL (with depth buffering) using material properties and multiple point light sources (of different properties) for illumination.

### OpenGL interaction:
Switching between flat and smooth shading is allowed, where the normals of the sphere shall be provided explicitly for smooth shading. Also, interactively switching on and off different light sources is allowed and changing the material properties (ambient, diffuse, and
specular reflection coefficient as well as specular reflection exponent).

## sample output



<img src="https://github.com/sabean/Computer-Graphics/blob/master/RAY-CASTING/images/sphere.jpg" width="500">

<img src="https://github.com/sabean/Computer-Graphics/blob/master/RAY-CASTING/images/suzanne.jpg" width="500">


<img src="https://github.com/sabean/Computer-Graphics/blob/master/RAY-CASTING/images/rabbit.jpg">


## Issue Reporting

If you have found a bug or if you have a feature request, please report them at this repository issues section. Please do not report security vulnerabilities on the public GitHub issue tracker. 

## Author

Sabin Bhandari

## License

This project is licensed under the MIT license. See the [LICENSE](LICENSE) file for more info.

