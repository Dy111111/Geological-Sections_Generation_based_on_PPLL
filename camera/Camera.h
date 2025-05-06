#pragma once
#define _USE_MATH_DEFINES
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <cmath>

class Camera
{
public:
	Camera(float fov, float aspect, float near, float far);
	bool isCamera = true;
	std::string type = "Camera";
	float fov;
	float zoom=1;
	float near;
	float far;
	float focus = 10;
	float aspect;

	glm::vec3 position;
	glm::vec3 up=glm::vec3(0,1,0);
	glm::quat quaternion;
	glm::mat4 viewMatrix;
	glm::mat4 matrixWorld;
	glm::mat4 matrixWorldInverse;
	glm::mat4 projectionMatrix;
	glm::mat4 projectionMatrixInverse;

	void updateProjectionMatrix();
	void lookAt(glm::vec3 target);
	void translateX(float distance);
	void translateY(float distance);
	void translateZ(float distance);
private:
	
};