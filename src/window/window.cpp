#include "window.h"

using namespace engine;

Window::Window(int width, int height, const char* title) {
	m_width		 = width;
	m_height	 = height;
	m_title		 = title;
	m_fullscreen = false;

	if (!init())
		glfwTerminate();
}

Window::Window(const char* title) {
	m_title		 = title;
	m_fullscreen = true;

	if (!init())
		glfwTerminate();
}

Window::~Window() {
	glfwDestroyWindow(m_window);

	glfwTerminate();
}

void resize_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

bool Window::init() {
	if (!glfwInit()) {
		std::cerr << "Error whilst initializing GLFW window" << std::endl;
		return false;
	}

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);

	if (m_fullscreen) {
		m_width  = vidmode->width;
		m_height = vidmode->height;
		m_window = glfwCreateWindow(m_width, m_height, m_title, monitor, NULL);
	}
	else
		m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);

	if (!m_window) {
		std::cerr << "Error whilst creating GLFW window" << std::endl;
		return false;
	}

	if (!m_fullscreen)
		glfwSetWindowPos(m_window, (vidmode->width - m_width) / 2, (vidmode->height - m_height) / 2);

	glfwShowWindow(m_window);
	glfwMakeContextCurrent(m_window);

	glfwSetFramebufferSizeCallback(m_window, resize_callback);

	if (glewInit() != GLEW_OK) {
		std::cerr << "Error whilst initializing GLEW" << std::endl;
		return false;
	}

	engine::Input input(m_window);
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	return true;
}

void Window::sync() {
	GLenum status = glGetError();
	while (status != GL_NO_ERROR) {
		std::cout << "Error with OpenGL: " << status << std::endl;
		status = glGetError();
	}

	Input::update();
	glfwPollEvents();
}

void Window::update() {
	glfwSwapBuffers(m_window);
}

void Window::enableDepthTest() const {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void Window::disableDepthTest() const {
	glDisable(GL_DEPTH_TEST);
}

void Window::enableVSync() const {
	glfwSwapInterval(1);
}

void Window::disableVSync() const {
	glfwSwapInterval(0);
}

void Window::enableTransparancy() const {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
}

void Window::disableTransparancy() const {
	glDisable(GL_BLEND);
}

void engine::Window::lockCursor() const {
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void engine::Window::unlockCursor() const {
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

bool Window::isOpen() const {
	return !glfwWindowShouldClose(m_window);
}

int Window::getWidth() {
	glfwGetFramebufferSize(m_window, &m_width, &m_height);
	return m_width;
}

int Window::getHeight() {
	glfwGetFramebufferSize(m_window, &m_width, &m_height);
	return m_height;
}

float Window::getAspectRatio() {
	return (float) getWidth() / (float) getHeight();
}

GLFWwindow* Window::getWindow() const {
	return m_window;
}

void Window::setMinVersion(GLuint major, GLuint minor) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
}