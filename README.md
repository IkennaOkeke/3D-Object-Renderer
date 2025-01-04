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

## How it works:<br />
To sum up how it works, this program utilizes the concepts of linear algebra (specifically vectors and ray intersection) as the foundation for its logic.<br />What happens (speaking in terms of the space of real 3-dimensional vectors) is that there is an imaginary camera at position (0, 0, 0), and a "viewport" at a position in front of the camera (For example, if you were taking a picture, the viewport would be the portion of the world that your camera can see — the image that your camera would show you when the picture is taken).<br />The focal length is the distance between the camera and the viewport (the z value of the viewport, or the "zoom" of the camera), and the viewport height/width determines how much the camera can see of the imaginary 3D world.<br />Essentially, what the program does is iterate through each pixel (the image dimensions) in the viewport, and check to see if there is a sphere at that position.<br />To do this, the program casts a ray (given by the formula (p + td), where 'p' is the starting point of the ray, 'd' is the direction the ray points to, and 't' is the time it takes for that ray to reach the given direction vector) from the camera to the center of that specific pixel in the viewport.<br />The program then checks to see if that ray intersects with any of the given spheres (given by the formula (|x-c|^2 = r^2), where x is a vector located on the surface of the sphere, c is a vector at the center of the sphere, and r is the radius of the sphere) by iterating through each sphere and solving for the time value (t) of the sphere equation (|x-c|^2 = r^2), where x is given by the current casted ray (doing this will give a polynomial, which the program then applies the quadratic equation to, giving us our time value/s).<br />What this does is check to see that a ray (which you can visualize as a line in the 3D space) hits the sphere at any point in time in that imaginary 3D world.<br />For example, if the time given by the quadratic equation is nonexistent (no solutions to the polynomial), then there will never be a point in time where the ray intersects with the sphere, meaning that the current pixel the program is on should not display a portion of that sphere.<br />If there are two 't' values, however, the ray will enter the sphere at one point in time, and exit at another point in time (unless the camera is inside the sphere or other complications, in which case the program would get one 't' value), meaning that the current pixel should display the point at which the ray FIRST intersects with the sphere.<br /><br /> If the ray cast from the current pixel has zero intersections whatsoever, then the program knows to simply print the background colour (given by the user). If the ray only intersects with one sphere, then we colour the pixel based on that sphere's colour and shade accordingly. If the ray hits more than one sphere, however, then the program simply stores the smallest time value and colours the pixel based on the sphere which gave us that value.<br /><br />In order to colour each pixel properly, the program uses a formula which takes the user's light-source position and direction vectors to shade the current pixel, based on the distance between the point on the surface of the sphere that the original casted ray hit and the light source.<br />The program also must check for shadows, which occurs when the ray casted from the surface of one sphere to the light source intersects with another sphere. Similarly to our previous logic, the program does this by iterating through each sphere and checking the time values that this gives.<br />If there are no time values, then that portion of the sphere will always see light, so it should be coloured based on the given light intensity formula.<br />If there are t-values, then the program shades the current pixel dark to imitate a shadow.<br /><br />Finally, the program writes the current pixel's RGB value to the ppm file. <br />The program continues this process until every pixel has been checked, and then terminates.<br /><br />

## More Examples:<br />

Input: <br />

```
640 480
2.0
1.0
20.0 20.0 10.0 1000.0
4
0x1188EE 0xDD2266 0xDD7700 0x11CC66
0
3
2.0 0.0 -5.0 2.0 2
-2.0 0.0 -5.0 2.0 3
0.0 -102.0 -5.0 100.0 1
```

<br />
Output: <br /><br />

![](output2.png) <br /><br /><br />

Input: <br />

```
640 480
2.0
5.0
-10.0 10.0 -30.0 500.0
5
0x6ABADA 0xFFFF00 0xFF4500 0x00FF00 0x0000FF
2
4
-6.0 0.0 -50.0 5.0 4
3.0 0.0 -55.0 3.0 3
10.0 0.0 -60.0 2.0 1
15.0 0.0 -65.0 1.0 0
```

<br />
Output: <br /><br />

![](output3.png) <br /><br />









