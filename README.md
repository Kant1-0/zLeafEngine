# zLeafEngine
![Title](/doc/title-zleafengine.jpg)
3D rendering engine based on new Khronos API: Vulkan. 
Built with Visual Studio 2015 on Windows 10 but Vulkan API and any other used libraries aim to be cross-platform.

## Specifications
ZLeaf Engine first iniate GLFW to create a window instance then create the Vulkan Instance.
Vulkan API will pick the most efficient graphic card available (or return if none exists) and create a logical device
for it. 

The graphic pipeline is designed to 

zLeaf Engine can load most of the obj format and parse it with textures UV mapping. 
The object is stored in a Vertex Buffer linked to a Uniform Buffer Object. The UBO holds the 3 matrix 

A debug validation layer is also created at the very beginning to hold any error output

## Compiling
To compile this project you must download these additional libraries and headers, 
then link to them to your project using the IDE of your choice. 
This project is currently built with Visual Studio 2015.

* [Vulkan 1.0.24.0](https://vulkan.lunarg.com/sdk/home) (Open Publication License)
* [GLFW 3.2.1](http://www.glfw.org/download.html) (Zlib-Libpng License)
* [STB_Image 2.12 & STB_Image_Resize 0.91](https://github.com/nothings/stb) (Public Domain)
* [TinyOBJ 1.0.0](https://syoyo.github.io/tinyobjloader/) (MIT license)
* [GLM 0.9.8.2](http://glm.g-truc.net/0.9.8/index.html) (Happy Bunny License)

## Preview
![Render](/doc/render-zleafengine.jpg)
![Cmd-Output](/doc/cmd-zleafengine.jpg)
