#include "Window.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Shader* Window::shader = nullptr;

void Window::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_camera = new Camera();
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

bool Window::create(int _w, int _h, const char* _title) {
    m_window = glfwCreateWindow(_w, _h, _title, NULL, NULL);
    if (m_window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    // Set le context de la fenêtre a tread actuel
    glfwMakeContextCurrent(m_window);

    // Permet d'avoir une callback quand on set un nouveau frame buffer
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
    glfwSetWindowSizeCallback(m_window, window_size_callback);

    // Interval entre le swap de buffer
    glfwSwapInterval(1);

    // Charger tout les pointeur sur fonction de OpenGL > Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return false;
    }
    glEnable(GL_DEPTH_TEST);

    /*int width, height;
    glfwGetWindowSize(m_window, &width, &height);
    glfwSetCursorPos(m_window, (float)width / 2, (float)height / 2);*/
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return true;
}

Camera* Window::getCamera() {
    return this->m_camera;
}

void Window::getMousePos(double* posX, double* posY) {
    glfwGetCursorPos(m_window, posX, posY);
}

void Window::setShader(Shader* _shader) {
    shader = _shader;
}

bool Window::isOpen() {
    return !glfwWindowShouldClose(m_window);
}

void Window::close() {
    glfwSetWindowShouldClose(m_window, true);
}

bool Window::isKeyPressed(int _key) {
    return glfwGetKey(m_window, _key) == GLFW_PRESS;
}

void Window::clear(float _r, float _g, float _b) {
    glClearColor(_r, _g, _b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::pollEvents() {
    // Swap buffers and poll IO events
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void Window::update(float _time) {
   
    m_camera->udpate(this, _time);
}

Window::~Window() {
    // Clear all allocated GLFW resources
    glfwTerminate();
}

void Window::window_size_callback(GLFWwindow* window, int width, int height) {
    if (width != 0 || height != 0) {
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
        shader->SetMatrix4("projection", projection);
    }
    
}
