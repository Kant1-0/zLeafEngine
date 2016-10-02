/*
	GInputCallback_Base class to call inputKeyCallback function within class 
	but with an absolute void type.
	To select a specific instance as active callback handler call 
	its inherited void: GInputCallback_Base::setEventHandling().
*/

#ifndef _GINPUT_BASE_H
#define _GINPUT_BASE_H

#include "stdafx.h"

class GInput_Base
{
	public:
		//Purely abstract function
		virtual void inputKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
		virtual void inputMouseCallback(GLFWwindow* window, double xpos, double ypos) = 0;
		virtual void inputScrollCallback(GLFWwindow* window, double xoffset, double yoffset) = 0;

		//Technically setEventHandling should be finalized so that it doesn't get overwritten by a descendant class.
		static GInput_Base *eventHandlingInstance;
		virtual void setEventHandling()
		{
			eventHandlingInstance = this;
		}

		//Dispatch functions
		static void inputKeyCallback_Dispatch(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (eventHandlingInstance)
				eventHandlingInstance->inputKeyCallback(window, key, scancode, action, mods);
		}
		static void inputMouseCallback_Dispatch(GLFWwindow* window, double xpos, double ypos)
		{
			if (eventHandlingInstance)
				eventHandlingInstance->inputMouseCallback(window, xpos, ypos);
		}
		static void inputScrollCallback_Dispatch(GLFWwindow* window, double xoffset, double yoffset)
		{
			if (eventHandlingInstance)
				eventHandlingInstance->inputScrollCallback(window, xoffset, yoffset);
		}
};

#endif // !_GINPUTCALLBACK_H
