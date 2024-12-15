#ifndef WINDOW_H__
#define WINDOW_H__

#include "Shader.h"
#include "Camera.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
	GLFWwindow* m_window;
	Camera* m_camera;

public:
	static Shader* shader;

	~Window();
	void init();
	bool create(int _w, int _h, const char* _title);
	Camera* getCamera();
	void getMousePos(double* posX, double* posY);
	void setShader(Shader* _shader);
	bool isOpen();
	void close();
	bool isKeyPressed(int _key);
	void clear(float _r, float _g, float _b);
	void pollEvents();
	void update(float _time);

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height); 
	static void window_size_callback(GLFWwindow* window, int width, int height);
};

#endif