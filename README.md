# Ray-Tracer
- Hello Everyone. I will attempt to build a ray tracer based on the following book, [Computer graphics from Scratch](https://www.gabrielgambetta.com/computer-graphics-from-scratch/)
- This will be based on **Part I : Ray tracing**
- The source code in book is given in `javaScript` but I will be re-writing the code into `c++`

## Building and compiling files
### Prerequesits:
- make sure to have a c++ compiler supporting C++17 or higher
- make sure you have CMake installed on your system
### Building and compiling with visual studio community
1. download this repo
2. Launch Visual Studio, select **Open a local folder**, and choose your project's root repository directory.
3. Visual Studio will automatically detect your `CMakeLists.txt` file and configure the build environment in the background.
4. Wait for configuration to finish, select `RayTracer.exe` from the **Select Startup Item** dropdown at the top, and press the green hollow run button to compile and run

## locating the output image file
- This ray-tracer will produce a ppm file called `imageFile.ppm`
- The location of the file is in the same folder as the `RayTracer.exe` file
- If you are using Visual studio community, Go to: `Ray-Tracer>out>build>x64-Debug`

## editing the canvas file
- you can change the dimesnions of the output ppm file by modifiying the canvas width and canvas height
- locate the `Constants.h` header file
- modify the values `CANVAS_WIDTH` and `CANVAS_HEIGHT` on line 9 and 10 respectively

## Extending the Ray Tracer
The last part of the book talks about how we can extend the Ray Tracer to make it better and we will be implementing those changes
### Changing the location of the camera:
- go the header file called `Constants.h` located in the `core` folder: **`core\Constants.h`**
- go to line **16** and you will find the variable called `origin` and change it to where you want to put the camera

### Rotate the Camera
This section explains what happens when you rotate the camera:
- When camera is rotated, the view port must also be rotated
- This is to make sure the view port remains as a perfect square infront of the camera lens
- `V` is the direction vector from camera location to location on viewport so we multiply that by the rotation matrix
- To edit the rotation matrix: go to the header file called `Constants.h` located in the `core` folder: **`core\Constants.h`**
- go to line **19** and edit the matrix there