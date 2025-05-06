#include"Camera.h"
Camera::Camera(float fov = 50, float aspect = 1, float near = 0.1, float far = 2000) :
	fov(fov),
	aspect(aspect),
	near(near),
	far(far)
{
	updateProjectionMatrix();
}
void Camera::lookAt(glm::vec3 target) {
	viewMatrix = glm::lookAt(position, target, up);
	quaternion = glm::toQuat(viewMatrix);//?
}

void Camera::translateX(float distance) {
	glm::vec3 v = glm::vec3(1, 0, 0);
	v = glm::normalize(v * quaternion);
	position += v*distance;
}
void Camera::translateY(float distance) {
	glm::vec3 v = glm::vec3(0, 1, 0);
	v = glm::normalize(v * quaternion);
	position += v * distance;
}
void Camera::translateZ(float distance) {
	glm::vec3 v = glm::vec3(0, 0, 1);
	v = glm::normalize(v * quaternion);
	position += v * distance;
}

void Camera::updateProjectionMatrix() {
	this->projectionMatrix = glm::perspective(glm::radians(fov), aspect, near, far);
}