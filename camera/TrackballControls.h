#pragma once
#include"Camera.h"
#include<GLFW/glfw3.h>
#include<iostream>
#include<limits>
#include<cmath>
#include<functional>
class TrackballControls
{
public:
	using CallbackFunc = std::function<void()>;
	Camera* camera;
	GLFWwindow* window;
	TrackballControls(Camera* camera, GLFWwindow* window);
	enum STATE {
		NONE = -1,
		ROTATE = 0,
		ZOOM = 1,
		PAN = 2,
		TOUCH_ROTATE = 3,
		TOUCH_ZOOM_PAN = 4
	};
	float screenWidth;
	float screenHeight;
	float rotateSpeed = 1.0;
	float zoomSpeed = 1.2;
	float panSpeed = 0.3;
	float minDistance = 0;
	float maxDistance = std::numeric_limits<double>::infinity();
	float minZoom = 0;
	float maxZoom= std::numeric_limits<double>::infinity();
	float dynamicDampingFactor = 0.2;
	bool staticMoving = false;
	bool noRotate = false;
	bool noZoom = false;
	bool noPan = false;
	glm::vec3 target;
	const float EPS = 0.000001;
	glm::vec3 lastPosition;
	float lastZoom = 1;
	STATE _state = STATE::NONE;
	STATE _keyState = STATE::NONE;
	glm::vec3 _eye;
	glm::vec3 _lastAxis;
	float _lastAngle=0;
	glm::vec2 _movePrev;
	glm::vec2 _moveCurr;
	glm::vec2 _zoomStart;
	glm::vec2 _zoomEnd;
	glm::vec2 _panStart;
	glm::vec2 _panEnd;
	void rotateCamera();
	void zoomCamera();
	void panCamera();
	void checkDistance();
	void update();
	void reset();
	glm::vec2 getMouseOnScreen(double x,double y);
	glm::vec2 getMouseOnCircle(double x, double y);
	//for reset
	glm::vec3 target0;
	glm::vec3 position0;
	glm::vec3 up0;
	float zoom0;

	void glfw_keyboard_input_callback(GLFWwindow* window);
	void OnResize(GLFWwindow* window, int w, int h);
	void glfw_cursor_pos_callback(GLFWwindow* window, double x, double y);
	void glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void glfw_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
	float lat = 0;
	float lon = 0;
};