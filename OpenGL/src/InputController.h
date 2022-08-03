#pragma once

#include "GLFW/glfw3.h"
#include "glm/vec2.hpp"

#define 	MOUSE_BUTTON_1  0
#define 	MOUSE_BUTTON_2  1
#define 	MOUSE_BUTTON_3  2
#define 	MOUSE_BUTTON_4  3
#define 	MOUSE_BUTTON_5  4
#define 	MOUSE_BUTTON_6  5
#define 	MOUSE_BUTTON_7  6
#define 	MOUSE_BUTTON_8	7

#define		MOUSE_RELEASE	0
#define		MOUSE_PRESS		1

#define		MOUSE_NONE		0
#define		MOUSE_RELEASED	1
#define		MOUSE_PRESSED	2

class InputController
{
public:

	InputController();

	void set_cursor_position(float xpos, float ypos);
	void set_mouse_action(int button, int action);
	void set_scroll(double xoffset, double yoffset);

	void mouseActionCallBack(void (*function)(int action)) { m_ActioncallBackFunc = function; }
	void mouseScrollCallBack(void (*function)(double xoffset, double yoffset)) { m_ScrollcallBackFunc = function; };

	glm::vec2 getCursorPosition() const {
		return m_cursorPos;
	}

	int getMouseAction() const {
		return m_mouseAction;
	}

	int getMouseButton() const {
		return m_mouseButton;
	}

	int getInputChanged() const {
		return m_inputChanged;
	}

private:
	static inline glm::vec2 m_cursorPos;
	static inline glm::vec2 m_startPos;
	static inline glm::vec2 m_endPos;
	static inline int m_mouseButton;
	static inline int m_mouseAction;
	static inline int m_inputChanged;

	static inline void(*m_ActioncallBackFunc)(int action);
	static inline void(*m_ScrollcallBackFunc)(double xoffset, double yoffset);

};