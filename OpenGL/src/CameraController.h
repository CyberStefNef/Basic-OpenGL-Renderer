#pragma once

#include "glm/glm.hpp"
#include "InputController.h"

class CameraController
{
public:
	CameraController();
	~CameraController();

	glm::mat4 getView();
	glm::mat4 getProj();

private:

	glm::vec2 m_startPos, m_endPos;

	float m_scale;
	int m_mouseButtonState;

	glm::vec3 m_View;
	glm::vec3 m_Offset;
	glm::mat4 m_Proj;

	InputController m_inputController;

};