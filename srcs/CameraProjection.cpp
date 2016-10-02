
#include "CameraProjection.h"

namespace zLeafEngine
{
	void CameraProjection::initView()
	{
		cameraView.pos = glm::vec3(3.0f, 3.0f, 3.0f);
		cameraView.target = glm::vec3(0.0f, 0.0f, 0.0f);
		cameraView.up = glm::vec3(0.0f, 0.0f, 1.0f);
	
		perspectiveProj.fov = glm::radians(45.0f);
		perspectiveProj.ratio = swapChainExtent.width / (float)swapChainExtent.height;
		perspectiveProj.nearView = 0.1f;
		perspectiveProj.farView = 10.0f;
	
		modelView = glm::rotate(glm::mat4(), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	}
}