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
1. To set up the BVH, we need to construct the data structure that will act as the BVH
2. Create another data structure which is called `ListSpheres`

##### constructing the BVH data structure:
- the files that set up this data structure is located in: `scene\BoundingTree.h` and `scene\BoundingTree.cpp`
- the data structure is essentially a binary tree and each node in the binary tree is composed of two parts: 
- a value which I will call the `rootNode` which represents the bounding box that is used to encapsulate the child bounding boxes or actual spheres of the child trees
- and two smart pointers - `leftTree` and `rightTree` that point to the left and right child sub trees.
- the value of a given node called `rootNode` is of type `BoundingBox`. A Bounding Box is defined by three characterisitics: the minimum and maximum co-ordinates of its vertices and a sphere object it holds, as well as a boolean value indicating weather its a child node
- the minimum and maximum coordinates are enough to reconstruct the boundingBox and the pointer if it takes a value of null, signifies that the `rootNode` value is a left node and if not, has two child trees left and right

##### `ListSpheres` data structure:
- This data structure is useful for setting up an instance of the BVH data structure and the header and cpp file are located in the scene folder
- Now this data structre is composed of important members necessary to establishing the BVH data structure
- First it contains the spheres which is a vector composed of all the spheres in the scene to render. 
- Second of all, it contains a character which stores the dimensions along which the spheres are most spread out
- Third of all, it contains the important methods needed to establihs the BVH.

1. In order, to first establish the BVH, we need to stort the data based on the dimension it is most spread out in: the `char max_dimension`
2. To do this, we need to calculate the dimension in which the spheres are the most spread out in and this is done by the method: `void ListSpheres::setTheMaxDimension()`
3. Next, we need to sort the data based on this dimension, for example if the max_dimension was x, then the spheres would be sorted in ascending order based on the x part of their center coordinates: `void ListSpheres::sort()`
4. Finally, we use a divide and conquer technique - where I would take the sorted vector array of spheres and repeateldy divide the list - calculate the bounding box for the given spheres and repeat this process whilst setting up the bounding tree: `void ListSpheres::setBoundingTree(std::span<Sphere>data, BoundingTree& currentBoundingTree, int start_index, int count)`
5. This would terminate when the number of spheres left was One, in which the root node bounding box would have its isChild attrubute set to true and the bounding trees left and right pointers would be null

**Searching for the intersection**
Next we need to seach for the bounding box and hence the correct sphere and the corresponding t value for a given ray which is defined by its starting value - P and direction vector D
1. The ray is shooted into the scene, and the program checks weather or not it intersects with the bounding box that encomposses all the current spheres,
2. if it doesnt, the background color of BLACK is returned. 
3. If it does, a recursive search algorithm - pre order traversal is used and it terminates when u get to a bounding box that is a child node, has no more sucessors and therefore can no longer terimnate and that bounding box actually contains the sphere and no more other bounding boxes
4. In the event, that a ray intersects two smaller boxes as the same time, in a given bounding box that it is in, we always take the bounding box that provides the smaller t value because atm in time, the ray would be the same for both bounding boxes and so would the origin of the ray - so taking the smaller value of t means taking the bounding box that is closer to origin
5. This method also accounts for rays that originate inside a bounding box and work the same way.
6. If anywhere in the process, once a ray intersects a box and then longer intersects any more boxes within that box, we can say the ray hasnt intersected any spheres thankfully.
7. Also the t returned when a ray actaully hits a sphere, isnt the t that is derived when the ray hits the box, its the actual one derived when the ray hits the sphere