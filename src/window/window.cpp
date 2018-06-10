#include "window.h"

using namespace engine;

Window::Window(int width, int height, const char* title, bool resizable, int monitorIndex) : m_width(width), m_height(height), m_title(title), m_fullscreen(false) {
	if (!init(monitorIndex, resizable))
		glfwTerminate();
}

Window::Window(const char* title, int monitorIndex) : m_title(title), m_fullscreen(true) {
	if (!init(monitorIndex))
		glfwTerminate();
}

Window::~Window() {
	glfwDestroyWindow(m_window);

	glfwTerminate();
}

void Window::resize_callback(GLFWwindow* window, int width, int height) {
	static_cast<Window*>(glfwGetWindowUserPointer(window))->setWindowSize(width, height);
}

bool Window::init(int monitorIndex, bool resizable) {
	if (!glfwInit()) {
		std::cerr << "Error whilst initializing GLFW window" << std::endl;
		return false;
	}

	int count;
	GLFWmonitor** monitors = glfwGetMonitors(&count);
	if (monitorIndex > count - 1)
		monitorIndex = 0;

	GLFWmonitor* monitor = monitors[monitorIndex];
	const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);

	if (!m_fullscreen)
		glfwWindowHint(GLFW_RESIZABLE, resizable);

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

	if (!m_fullscreen) {
		int x, y;
		glfwGetMonitorPos(monitor, &x, &y);
		glfwSetWindowPos(m_window, x + (vidmode->width - m_width) / 2, y + (vidmode->height - m_height) / 2);
	}

	glfwShowWindow(m_window);
	glfwMakeContextCurrent(m_window);

	glfwSetWindowUserPointer(m_window, this);

	glfwSetFramebufferSizeCallback(m_window, resize_callback);

	if (glewInit() != GLEW_OK) {
		std::cerr << "Error whilst initializing GLEW" << std::endl;
		return false;
	}

	engine::Input input(m_window);
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	m_delta = 0.0f;
	m_lastTime = glfwGetTime();
	m_tickSpeed = 60.0f;

	Input::width = m_width;
	Input::height = m_height;

	return true;
}

void Window::update() {
	GLenum status = glGetError();
	while (status != GL_NO_ERROR) {
		status = glGetError();
		if (m_prevError == status)
			continue;
		std::cout << "Error with OpenGL: " << status << std::endl;
		m_prevError = status;
	}

	Input::update();
	glfwPollEvents();
}

void Window::sync() {
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

bool Window::isOpen() {
	float now = glfwGetTime();
	m_delta += (now - m_lastTime) / (1.0f / m_tickSpeed);
	m_lastTime = now;

	return !glfwWindowShouldClose(m_window);
}

bool engine::Window::canUpdate() {
	if (m_delta >= 1) {
		m_delta--;
		return true;
	}

	return false;
}

int Window::getWidth() const {
	return m_width;
}

int Window::getHeight() const {
	return m_height;
}

float Window::getTickSpeed() const {
	return m_tickSpeed;
}

float Window::getAspectRatio() const {
	return float(getWidth()) / float(getHeight());
}

GLFWwindow* Window::getWindow() const {
	return m_window;
}

void Window::setTickSpeed(float tickSpeed) {
	m_tickSpeed = tickSpeed;
}

void Window::setIcon(const char** paths, int count) {
	GLFWimage* images = new GLFWimage[count];
	for (int i = 0; i < count; i++)
		images[i] = File::loadGLFWimage(paths[i]);

	glfwSetWindowIcon(m_window, count, images);

	delete[] images;
}

void Window::setCursor(const char* path, int xHot, int yHot) {
	GLFWimage image = File::loadGLFWimage(path);

	GLFWcursor* cursor = glfwCreateCursor(&image, xHot, yHot);

	glfwSetCursor(m_window, cursor);
}

void Window::setWindowSize(int width, int height) {
	Input::width = width;
	Input::height = height;
	m_width = width;
	m_height = height;
	glfwSetWindowSize(m_window, width, height);
	glViewport(0, 0, width, height);
}

void Window::setMinVersion(GLuint major, GLuint minor) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
}