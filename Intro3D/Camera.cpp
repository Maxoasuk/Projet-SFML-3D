#include "Camera.h"

#include "Window.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera::Camera() : 
	m_lastMousePosX(NULL),
	m_lastMousePosY(NULL),
	m_position(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_yaw(0.f), m_pitch(0.f),
	m_up(glm::vec3(0.f, 1.f, 0.f)), 
	m_front(glm::vec3(0.f, 0.f, 1.f)), 
	m_right(glm::vec3(1.f, 0.f, 0.f)) {}

void Camera::setPosition(float x, float y, float z) {
	this->m_position = glm::vec3(x, y, z);
}
void Camera::setPosition(glm::vec3 _position) {
	this->m_position = _position;
}

void Camera::setRotation(float _yaw, float _pitch) {
	m_yaw = _yaw;
	m_pitch = _pitch;
}

glm::mat4 Camera::getView() {
	glm::mat4 view = glm::lookAt(m_position, m_position + m_front, m_up);
	return view;
}

void Camera::udpate(Window* window, float _time) {
	float speedRotation = 25.f;
	double posX, posY;
	window->getMousePos(&posX, &posY);

	if (m_lastMousePosX == NULL || m_lastMousePosY == NULL) {
		m_lastMousePosX = posX;
		m_lastMousePosY = posY;
	}

	m_yaw += (m_lastMousePosX - posX) * speedRotation * _time;
	m_pitch += (m_lastMousePosY - posY) * speedRotation *  _time;

	glm::mat4 rotationMat = glm::rotate(glm::mat4(1.f), glm::radians(m_yaw), glm::vec3(0.f, 1.f, 0.f));
	m_right = glm::normalize(glm::vec3(rotationMat * glm::vec4(glm::vec3(1.f, 0.f, 0.f), 1.f)));

	rotationMat = glm::rotate(rotationMat, glm::radians(m_pitch), m_right);
	m_front = glm::normalize(glm::vec3(rotationMat * glm::vec4(glm::vec3(0.f, 0.f, 1.f), 1.f)));

	m_up = glm::normalize(glm::cross(m_front, m_right));

	m_lastMousePosX = posX;
	m_lastMousePosY = posY;

	float speed = 10.f;
	if (window->isKeyPressed(GLFW_KEY_D)) {
		m_position -= m_right * speed * _time;
	}
	if (window->isKeyPressed(GLFW_KEY_A)) {
		m_position += m_right * speed * _time;
	}
	if (window->isKeyPressed(GLFW_KEY_SPACE)) {
		m_position += m_up * speed * _time;
	}
	if (window->isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
		m_position -= m_up * speed * _time;
	}
	if (window->isKeyPressed(GLFW_KEY_W)) {
		m_position += m_front * speed * _time;
	}
	if (window->isKeyPressed(GLFW_KEY_S)) {
		m_position -= m_front * speed * _time;
	}
}