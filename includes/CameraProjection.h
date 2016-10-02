/*
  Camera view
*/

#ifndef _CAMERA_H
#define _CAMERA_H

#include "stdafx.h"
#include "DepthBuffers.h"

namespace zLeafEngine
{
	class CameraProjection : public DepthBuffers // -> DrawFrame
	{
	public:
		struct Camera
		{
			glm::vec3 pos;
			glm::vec3 target;
			glm::vec3 up;
		};

		struct Projection
		{
			float fov;
			float ratio;
			float nearView;
			float farView;
		};

	protected:
		//Camera
		Camera cameraView;

		//Projection
		Projection perspectiveProj;

		//Model
		glm::mat4 modelView;

		//Init View
		void initView();
	};
}


#endif // !_CAMERA_H
