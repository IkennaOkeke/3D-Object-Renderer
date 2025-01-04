# 3D-Object-Renderer
This program is a 3-D shape renderer by Ikenna Okeke.<br /><br /><br /><br />
To use this program, download the .exe file, as well as the input.txt and output.ppm files (make sure they are all in the same folder).<br />
Before running the executable, you must write input.txt, which may require some knowledge on the inner workings of the program (provided further below). <br /><br /><br />

The formatting of input.txt should be like so:<br /><br />
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
<br /><br />

Now you will be able to run the executable. <br />
To run the executable, open up your terminal, navigate to the directory of the downloaded files (cd "directory-location"), and run the executable using the command "./3D_Obj_Renderer.exe input.txt output.ppm".<br /><br />

To view the output.ppm file, you can drop the file in an online .ppm viewer like this one: [PPM Viewer](https://www.cs.rhodes.edu/welshc/COMP141_F16/ppmReader.html).<br />
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
<br /><br />

This gives: <br /><br />
![](output.png)








