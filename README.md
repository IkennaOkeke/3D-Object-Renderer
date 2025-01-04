# 3D-Object-Renderer
This program is a 3-D shape renderer by Ikenna Okeke.<br /><br />
To use this program, download the .exe file, as well as the input.txt and output.ppm files (make sure they are all in the same folder).<br />
Before running the executable, you must write input.txt, which may require some knowledge on the inner workings of the program (provided further below). <br /><br />
The formatting of input.txt should be like so:  

```
<image width (int)> <image height (int)>
<viewport height (float)>
<focal length (float)>
<light position (3float --> x, y, z)> <light brightness (float)>
<number of colors `m` (int)>
<color 1 (HEX)> <color 2 (HEX)> ... <color m (HEX)>
<background color index (int)>
<number of spheres `n` (int)>
<sphere 1 position (3float)> <sphere 1 radius (float)> <sphere 1 color index (int)>
<sphere 2 position (3float)> <sphere 2 radius (float)> <sphere 2 color index (int)>
...
<sphere n position (3float)> <sphere n radius (float)> <sphere n color index (int)>
```

<br />
Now you will be able to run the executable.  
To run the executable, open up your terminal, navigate to the directory of the downloaded files (cd "directory-location"), and run the executable using the command "./3D_Obj_Renderer.exe input.txt output.ppm".<br /><br />

To view the output.ppm file, you can drop the file in an online .ppm viewer like this one: [PPM Viewer](https://www.cs.rhodes.edu/welshc/COMP141_F16/ppmReader.html).  

Or, if you use VSCode, you can download the PPM extension and view the file within VSCode.<br /><br />
The provided input.txt file in the repository has been pre-made with the following specifications: <br /><br />

```
400 300
2.0
1.0
0.0 0.0 -10.0 100.0
3
0x11BBFF 0xFFAA11 0xFF0033
0
4
-100 0.0 -10  90 1
 100 0.0 -10  90 1
  -5 0.0 -11   2 2
   5 0.0 -11   2 2
```

<br />
This gives: <br /><br />

![](output.png) <br /><br />

To sum up how it works, this program utilizes the concepts of linear algebra (specifically vectors and ray intersection) as the foundation for its logic.  What happens (speaking in terms of the space of real 3-dimensional vectors) is that there is an imaginary camera at position (0, 0, 0), and a "viewport" at a position in front of the camera (For example, if you were taking a picture, the viewport would be the portion of the world that your camera can see — the image that your camera would show you when the picture is taken).  The focal length is the distance between the camera and the viewport (the z value of the viewport, or the "zoom" of the camera), and the viewport height/width determines how much the camera can see of the imaginary 3D world.  Essentially, what the program does is iterate through each pixel (the image dimensions) in the viewport, and checks to see if there is a sphere at that position.  To do this, the program casts a ray (given by the formula (p + td), where 'p' is the starting point of the ray, 'd' is the direction the ray points to, and 't' is the time it takes for that ray to reach the given direction vector) from the camera to the center of that specific pixel in the viewport.  The program then checks to see if that ray intersects with any of the given spheres (given by the formula (|x-c|^2 = r^2), where x is a vector located on the surface of the sphere, c is a vector at the center of the sphere, and r is the radius of the sphere) by iterating through each sphere and solving for the time value (t) of the sphere equation (|x-c|^2 = r^2), where x is given by the current casted ray (doing this will give a polynomial, which the program then applies the quadratic equation to, giving us our time value/s).  What this does is check to see that a ray (which you can visualize as a line in the 3D space) hits the sphere at any point in time in that imaginary 3D world.  For example, if the time given by the quadratic equation is nonexistent (no solutions to the polynomial), then there will never be a point in time that the ray intersects with the sphere, meaning that the current pixel we are on should not display a portion of that sphere.  If there are two 't' values, however, the ray will enter the sphere at one point in time, and exit at another point in time (unless the camera is inside the sphere or other complications, in which case we would get one 't' value), meaning that the current pixel should display the point at which the ray FIRST intersects with the sphere.










