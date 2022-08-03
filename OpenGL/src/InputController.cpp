#include "InputController.h"

#include <iostream>


InputController::InputController()
{
}

void InputController::set_cursor_position(float xpos, float ypos)
{
	m_cursorPos = { xpos, ypos };

	m_inputChanged = MOUSE_NONE;
}

void InputController::set_mouse_action(int button, int action)
{

	/*if (m_mouseButton == MOUSE_BUTTON_1 && m_mouseAction == MOUSE_PRESS && action == MOUSE_RELEASE)
		m_inputChanged = MOUSE_RELEASED;
	else if(m_mouseButton == MOUSE_BUTTON_1 && m_mouseAction == MOUSE_RELEASE && action == MOUSE_PRESS)
		m_inputChanged = MOUSE_PRESSED;
	else
		m_inputChanged = MOUSE_NONE;*/

	if(m_ActioncallBackFunc)
		m_ActioncallBackFunc(action);

	m_mouseButton = button;
	m_mouseAction = action;
}

void InputController::set_scroll(double xoffset, double yoffset)
{
	if (m_ScrollcallBackFunc)
		m_ScrollcallBackFunc(xoffset, yoffset);
}


//glm::vec2 InputController::get2DMovement()
//{
//	if (m_mouseButton == MOUSE_BUTTON_1 && m_mouseAction == MOUSE_PRESS) {
//		//std::cout << m_startPos.x - m_endPos.x << ", " << m_startPos.y - m_endPos.y << std::endl;
//		return { -(m_startPos.x - m_endPos.x )/ 960 *2, (m_startPos.y - m_endPos.y) / 720 * 2 };
//	}
//	return glm::vec2();
//}
