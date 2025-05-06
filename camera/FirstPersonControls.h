#pragma once
#include <corecrt_math_defines.h>
#include"Camera.h"
#include<GLFW/glfw3.h>
#include<iostream>
class FirstPersonControls
{
public:
	Camera* camera;
	GLFWwindow* window;
	FirstPersonControls(Camera* camera, GLFWwindow* window);
	bool isSroll = false;
	float movementSpeed = 1.0;
	float lookSpeed = 0.03;
	bool moveForward = false;
	bool moveBackward = false;
	bool moveLeft = false;
	bool moveRight = false;
	bool moveUp = false;
	bool moveDown = false;
	bool constrainVertical = false;
	float verticalMin = 0;
	float verticalMax = M_PI;
	double pointerX = 0;
	double pointerY = 0;
	double viewHalfX = 0;
	double viewHalfY = 0;
	float mapLinear(float x, float a1, float a2, float b1, float b2);
	glm::vec3 getFromSphericalCoords(float radius, float phi, float theta);
	void update(float delta);
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