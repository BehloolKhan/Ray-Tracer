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

### Rotating the Camera
This section explains what happens when you rotate the camera:
- When camera is rotated, the view port must also be rotated
- This is to make sure the view port remains as a perfect square infront of the camera lens
- `V` is the direction vector from camera location to location on viewport so we multiply that by the rotation matrix
- To edit the rotation matrix: go to the header file called `Constants.h` located in the `core` folder: **`core\Constants.h`**
- go to line **19** and edit the matrix there

### Parallelisation
- speeding up the ray tracer with parallisation
- if you go to **`main.cpp`** file, you will see this implemented it
- The way I did it, was I broke down the range of x_co-ordinates into chunks based on the number of availbale cores: `std::thread::hardware_concurrency_` on line `35`
- I then essentially performed the same function on the different chunks of x-coordinates_

### Shadows
- Another one to optimise ray tracer is to optimise by shadows
- If you go to line **175** in `core\methods.cpp`, you will see the method `isIntersection` being called which has replaced the method `closestIntersection` being called
- Before the new method was called, to decide if a there lay a sphere between p and a light source, we would calculate the closest sphere being intersected
- But in order for a shadow to form, The ray starting from point P, going towards light source must intersect with at least one sphere, and once we find one intersection, we can stop right there
- That is why the method `isIntersection` returns `true` once it finds just one intersection
- In addition, if a point P lies in a shadow, due to an intersection with a sphere, than there is a chance its neighbouting points also lie in a shadow
- The pointer on line **16** - `shadowSphere` points to `Sphere` object which is the Sphere that has recently caused a shadow

### Bounding Volume heirachy
- Another way to speed up a ray tracer is via Bounding Volume Heirachies
- A bounding volume heirachy is a spatial data structure used to store 3D objects in a scene.
- A spatial data structure is a data structure that attempts to store objects based on their position in a 3D scene
- The spatial data structure used to implement the bounding volume heirachy is a binary tree.
- When it comes to bounding volume heirachies: There are two parts, **setting up the bounding volume heirachy** and **traversing the bounding volume heirachy**

#### setting up the bounding volume heirachy
- the files that set up this data structure is located in: `scene\BoundingTree.h` and `scene\BoundingTree.cpp`
- the data structure is essentially a binary tree and each node in the binary tree is composed of two parts: 
- a value which I will call the `rootNode` which represents the bounding box that is used to encapsulate the child bounding boxes or actual spheres of the child trees
- and two smart pointers - `leftTree` and `rightTree` that point to the left and right child sub trees.
- the value of a given node called `rootNode` is of type `BoundingBox`. A Bounding Box is defined by three characterisitics: the minimum and maximum co-ordinates of its vertices and a pointer two a sphere object
- the minimum and maximum coordinates are enough to reconstruct the boundingBox and the pointer if it takes a value of null, signifies that the `rootNode` value is a left node and if not, has two child trees left