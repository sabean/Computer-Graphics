# Ray caster

This is an implementation of raster using C++

## set up

Given a 3D Cartesian coordinate system, the viewpoint is given as v = (0, 0, −2) and thescreen is given by the square with corners s 0 = (−1, −1, 0), s 1 = (−1, 1, 0), s 2 = (1, 1, 0), and s 3 = (1, −1, 0). Assuming perspective projection and range of sight 12, place three (not too small) spheres such that all three spheres are completely inside the view frustum and such that they partially occlude each other when looking at them from the viewpoint.

## Ray intersection

A ray from the viewpoint through the center of each pixel of the screen is sent and first intersection with any of the three spheres is computed. This requires to perform a ray-sphere intersection, where the ray is given in parametric form and the sphere in implicit form. The screen is partitioned into a number of pixels.

## Returning colors
In case the ray-sphere intersection did not deliver any intersection point, the respective pixel shall be assigned RGB color (0, 0, 0). In case the ray-sphere intersection delivered an intersection point, let (x, y, z) be the coordinates of the intersection point. In case the intersec-
tion was with the first sphere, RGB color ( 10−z/10 , 0, 0) shall be assigned to the pixel. In case the intersection was with the second sphere, RGB color (0, 10−z/10 , 0) shall be assigned to the pixel. In case the intersection was with the third sphere, RGB color (0, 0, 10−z
10 ) shall be assigned to the pixel. Note that the RGB values of the color are asssumed to be ∈ [0, 1] here.

## sample output


<img src="https://github.com/sabean/Computer-Graphics/blob/master/RASTER/image.jpg" width="500">

## Issue Reporting

If you have found a bug or if you have a feature request, please report them at this repository issues section. Please do not report security vulnerabilities on the public GitHub issue tracker. 

## Author

Sabin Bhandari

## License

This project is licensed under the MIT license. See the [LICENSE](LICENSE) file for more info.
