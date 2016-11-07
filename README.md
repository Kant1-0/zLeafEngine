# zLeafEngine
![Title](/doc/title-zleafengine.jpg)

3D rendering engine (x64) based on new Khronos API: Vulkan. 

Built with Visual Studio 2015 on Windows 10 but Vulkan API and any other used libraries aim to be cross-platform.

## Specifications
ZLeaf Engine first iniate GLFW to create a window instance then create the Vulkan Instance.
Vulkan API will pick the most efficient graphic card available (or return if none exists) and create a logical device
for it. 

The graphic pipeline is designed to init shader modules, vertex input, the viewport scissors, the rasterization,
handle multisampling, add a depth stencil and a color blending, then set the Pipeline Layout.
It finally combine all theses infos into the VkGraphicsPipeline elem.

![Graphic Pipeline](https://vulkan.lunarg.com/doc/view/1.0.26.0/linux/tutorial/images/GraphicsPipeline.png)

zLeaf Engine can load most of the obj format and parse it with textures UV mapping. 
The object is stored in a Vertex Buffer linked to a Uniform Buffer Object. The UBO holds the 3 matrix multiply
together at the end during the main Loop that renders the whole scenery.

The engine uses shader files so you doesn't to compile again if you wish to change the way color are proceed to vertices.

During the main loop GLFW can catch signal to update the Uniform Buffer and redraw it on screen. 
All done in real-time computing with the helps of a z-buffer and triangle rasterization. 

A debug validation layer is also created at the very beginning, if set to true, to catch any error thrown and print it.

A VkDeleter class made as a template helps to construct and destruct any Vk elements. It automatically frees it,
when the destructor is called by the engine.

## Commands

For now you can only rotate around the viewed object thanks to the Left-Arrow and Right-Arrow key.

If you wish to load another model, change the path in Global.cpp file.

## Compiling

To compile this project you must download these additional libraries and headers, 
then link to them to your project using the IDE of your choice. 
This project is currently built with Visual Studio 2015.

* [Vulkan 1.0.24.0](https://vulkan.lunarg.com/sdk/home) (Open Publication License)
* [GLFW 3.2.1](http://www.glfw.org/download.html) (Zlib-Libpng License)
* [STB_Image 2.12 & STB_Image_Resize 0.91](https://github.com/nothings/stb) (Public Domain)
* [TinyOBJ 1.0.0](https://syoyo.github.io/tinyobjloader/) (MIT license)
* [GLM 0.9.8.2](http://glm.g-truc.net/0.9.8/index.html) (Happy Bunny License)

## To Do

* UI with loading element option
* Full target camera and additional free camera
* View frustum culling
* Per-fragment point light with atenuation
* Shadow-mapping with FBO
* Particle system

## Preview

![Render](/doc/render-zleafengine.jpg)

![Cmd-Output](/doc/cmd-zleafengine.jpg)
