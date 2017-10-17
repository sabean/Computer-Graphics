# Ray Tracing

This is an implementation of ray tracing in C++

## Set-up
A scene with multiple objects is arranged, where at least one object is partially mirroring and one is partially transparent (with suitable refraction index).

## Shadows
For each intersection point of primary rays with the objects, shadow rays to the light sources is sent out and the local illlumination model accordingly is adjusted.

## Mirroring reflection
For each intersection point of primary rays with the mirroring objects, reflected rays are sent out and the result is combined with the result from above accordingly. Recursive calls up to a certain raytrace depth is applied.

## Refraction
For each intersection point of primary rays with the transparent objects, refracted rays is sent out and the result with the result from above is combined accordingly. Recursive calls up to a certain raytrace depth is applied.

## sample output

![](https://github.com/sabean/Computer-Graphics/blob/master/RAY-TRACING/images/final.jpg | width=50)
<!-- .element height="50%" width="50%" -->
![](https://github.com/sabean/Computer-Graphics/blob/master/RAY-TRACING/images/sp.jpg)
<!-- .element height="50%" width="50%" -->

## Issue Reporting

If you have found a bug or if you have a feature request, please report them at this repository issues section. Please do not report security vulnerabilities on the public GitHub issue tracker. 

## Author

Sabin Bhandari

## License

This project is licensed under the MIT license. See the [LICENSE](LICENSE) file for more info.

## References
<http://www.prinmath.com/csci5229/OBJ/index.html>

<http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading>
