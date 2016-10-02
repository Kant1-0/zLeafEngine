
#include "GWindow.h"

namespace zLeafEngine
{
	void GWindow::loadIcon(std::string path, GLFWimage *icon)
	{
		stbi_uc* pixels;
		int texWidth, texHeight, texChannels;

		pixels = stbi_load(path.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

		if (!pixels)
		{
			throw std::runtime_error("Failed to load texture image!");
		}

		icon->width = texWidth;
		icon->height = texHeight;
		icon->pixels = pixels;
	}
}