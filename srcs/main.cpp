
//Defines functions bodies for STB
#define STB_IMAGE_IMPLEMENTATION 

#include "App.h"

int		main()
{
	zLeafEngine::App app;

	try
	{
		app.run();
	}
	catch (const std::runtime_error &e)
	{
		std::cerr << e.what() << "\n";
		std::cin.get();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}