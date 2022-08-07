#include "CameraController.h"

#include "InputController.h"

#include <iostream>
#include "glm/gtc/matrix_transform.hpp"

static int mouseButtonState;
static float scrollState;

CameraController::CameraController()
	:m_View(glm::vec3(0, 0, 1)), m_Offset(glm::vec3(0,0,0)), m_scale(-6), m_camera(glm::vec3(0, 0, m_scale), 75.0f, 4.0f / 3.0f, 0.01, 1000.0f)
{	

	m_inputController.mouseActionCallBack([](int action){
		mouseButtonState = action + 1;
		});

	m_inputController.mouseScrollCallBack([](double xoffset, double yoffset) {
		scrollState = yoffset;
		});
}



CameraController::~CameraController()
{
}

glm::mat4 CameraController::getProj()
{

	if (scrollState != 0)
	{
		m_scale += scrollState * 0.5;
		if (m_scale < 0)
			m_scale = 0.1f;
		scrollState = 0;
	}
	
	m_Proj = glm::ortho(-2.0f * m_scale, 2.0f * m_scale, -1.5f * m_scale, 1.5f * m_scale, -1.0f, 1.0f);

	return m_Proj;
}

Camera CameraController::getPersCamera()
{
	if (scrollState != 0)
	{
		m_camera.MoveForward(scrollState * 0.1);
		scrollState = 0;
	}

	getView();

	return m_camera;
}


void CameraController::getView()
{
	glm::vec2 pos = m_inputController.getCursorPosition();


	if (mouseButtonState == MOUSE_PRESSED)
	{
		m_startPos = pos;
		mouseButtonState = MOUSE_NONE;
	}

	if (m_inputController.getMouseAction() == MOUSE_PRESS) {
		m_endPos = pos;
		m_Offset = glm::vec2(-(m_endPos.x - m_startPos.x) / 960, -(m_endPos.y - m_startPos.y) / 720);

		m_camera.MoveRight(m_Offset.x);
		m_camera.MoveUp(m_Offset.y);

		m_startPos = pos;
	}

	if (mouseButtonState == MOUSE_RELEASED)
	{
		mouseButtonState = MOUSE_NONE;
		m_Offset = { 0.0f, 0.0f };
	}

	
}
