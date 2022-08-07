#pragma once

#include "glm/glm.hpp"
#include "InputController.h"
#include "Camera.h"

class CameraController
{
public:
	CameraController();
	~CameraController();

	void getView();
	glm::mat4 getProj();
	Camera getPersCamera();

private:

	glm::vec2 m_startPos, m_endPos;

	float m_scale;
	int m_mouseButtonState;

	glm::vec2 m_View;
	glm::vec2 m_Offset;
	glm::mat4 m_Proj;

	InputController m_inputController;
	Camera m_camera;
};