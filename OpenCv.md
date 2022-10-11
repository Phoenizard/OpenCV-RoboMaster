## The Simple Giude of OpenCV

### Note:

This guide is suitable for the beginning learner on OpenCV which is going to take part in RoboMaster competition or want to learn how to use OpenCV in robot instead of clearly knowing its principle. OpenCV is available on both C++ and Python. However, since most of team in RoboMaster used C++, this guide won't introduce the use in Pyhton. Before you start reading. We recommand you to prepare an Linux environment(Ubuntu) and download ROS.

Some useful header files and namespaces are as below.

```c++
#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;
```

### CMake and Clion

We recommand to use Clion to make the programming since it is easy to set the environment, especially for Cmake file. You may apply to a Student Verification for the freely use.

   1. Install the template from Github, which is a folder.
       - Folder
         - .idea
         - cmake-build-debug
         - build
         - include
         - src
           - .gitignore
           - CMakeLists.txt
           - main.cpp
   2. Set the CMake: The cmake in template can search the opencv or package in your device automaticly. Therefore, you just need to edit the name of the project and turn the package (mainly openCV) to True.
        ```c++
            # =================CONFIGS======================
            
            ## project name
            set(PROJECT_NAME        "demo")

            # ================PACKAGES======================
                
            set(Threads             false)
            set(Eigen               false)
            set(OpenCV              true)
        ```
   3. Then reload the CMake project by clicking in right and choosing `Reload CMake Project`. Then you can write your code on `main.cpp` and run the code to see the result.      

### Static Picture Processing

#### Iuput and Display a Image

Just like the meaning of dome "Hello World", when it comes to OpenCV, the first thing we need to do is to load an image and display it.

##### Input an image

```c++
Mat image = imread("url");
```
Use imread can put your image into a variable which Class is Mat. Mat is unqiue in OpenCV which is just for storing pictures by decoding the channels value of an image and encoding the deta into a 2d array. You can also choose to the type of image by adding a constant.

```c++
Mat image = imread("url",0);
// Ruture the image in grey
```

Commonly,'1' means the origial image and '0' will change it into grey mood.

And usually, we will check whether the image in mat has been loaded successfully.

```c++
if(image.empty())
{
    cout << "No image" << endl;
    return -1;
}
```

##### Display an image

When you run the code. The system will create a window which is available to show your Mat variable. The process can be split into two part: define a window and add the picture.

There are two major element of a window you need to decide which is its name and its type. For now, we choose `WINDOW_NORMAL` or `WINDOW_AUTOSIZE`.

```c++
namedWindow("A string for its name",type); 
```

Then display your image.

```c++
imshow("Window's name",image's mat);
```

And don't forget to write a condition to close it.

`waitkey(0)` means if any buttom is pressed, then go next.

`destroywindow` means close all the windows you have created. 

```c++
waitKey(0); // wait for any key press
destroyWindow(windowName); // close the windows
```
