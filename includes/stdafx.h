/*
  Precompiled Header
*/


#ifndef _STDAFX_H
#define _STDAFX_H

//Automatically load the Vulkan header with GLFW
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

//GLM Headers
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//STB Header
#include <stb_image.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <vector>
#include <cstring>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <array>
#include <chrono>

#endif // !_STDAFX_H