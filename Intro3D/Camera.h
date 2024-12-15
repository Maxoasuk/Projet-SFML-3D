#ifndef CAMERA_H__
#define CAMERA_H__

#include <glm/glm.hpp>

class Window;

class Camera {
	glm::vec3 m_position;
	float m_yaw;
	float m_pitch;
	glm::vec3 m_up;
	glm::vec3 m_front;
	glm::vec3 m_right;
	double m_lastMousePosX;
	double m_lastMousePosY;

public: 
	Camera();
	void setPosition(float x, float y, float z);
	void setPosition(glm::vec3 _position);
	void setRotation(float _yaw, float _pitch);

	glm::mat4 getView();
	void udpate(Window* window, float _time);
};

#endif

