#include"FirstPersonControls.h"
FirstPersonControls::FirstPersonControls(Camera* camera, GLFWwindow* window):
	camera(camera),
	window(window) 
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	this->viewHalfX = width / 2.0;
	this->viewHalfY = height / 2.0;
};
void FirstPersonControls::update(float delta) {
	glm::vec3 targetPosition;
	const float actualMoveSpeed = delta * this->movementSpeed;
	if (this->moveForward)	this->camera->translateZ(-actualMoveSpeed);
	if (this->moveBackward)	this->camera->translateZ(actualMoveSpeed);
	if (this->moveLeft)		this->camera->translateX(-actualMoveSpeed);
	if (this->moveRight)	this->camera->translateX(actualMoveSpeed);
	if (this->moveUp)	this->camera->translateY(actualMoveSpeed);
	if (this->moveDown)	this->camera->translateY(-actualMoveSpeed);

	float actualLookSpeed = delta * this->lookSpeed;
	float verticalLookRatio = 1;
	if (this->constrainVertical) {
		verticalLookRatio = M_PI / (this->verticalMax - this->verticalMin);
	}
	lon -= this->pointerX * actualLookSpeed;
	lat -= this->pointerY * actualLookSpeed * verticalLookRatio;
	lat = fmax(-85, fmin(85, lat));

	float phi = glm::radians(90 - lat);
	const float theta = glm::radians(lon);
	if (this->constrainVertical) {
		phi = mapLinear(phi, 0, M_PI, this->verticalMin, this->verticalMax);
	}
	const glm::vec3 position = this->camera->position;
	targetPosition = getFromSphericalCoords(1, phi, theta)+position;
	this->camera->lookAt(targetPosition);
}

float FirstPersonControls::mapLinear(float x, float a1, float a2, float b1, float b2) {
	return b1 + (x - a1) * (b2 - b1) / (a2 - a1);
}

glm::vec3 FirstPersonControls::getFromSphericalCoords(float radius, float phi, float theta) {
	glm::vec3 result;
	const float sinPhiRadius = sin(phi) * radius;
	result.x = sinPhiRadius * sin(theta);
	result.y = cos(phi) * radius;
	result.z = sinPhiRadius * cos(theta);
	return result;
}

void FirstPersonControls::glfw_keyboard_input_callback(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) != GLFW_RELEASE || glfwGetKey(window, GLFW_KEY_UP) != GLFW_RELEASE)
	{
		this->moveForward = true;
	}
	else {
		this->moveForward = false;
	}
	if(glfwGetKey(window, GLFW_KEY_S) != GLFW_RELEASE || glfwGetKey(window, GLFW_KEY_DOWN) != GLFW_RELEASE)
	{
		this->moveBackward = true;
	}
	else {
		this->moveBackward = false;
	}
	if (glfwGetKey(window, GLFW_KEY_D) != GLFW_RELEASE || glfwGetKey(window, GLFW_KEY_RIGHT) != GLFW_RELEASE) {
		this->moveRight = true;
	}
	else {
		this->moveRight = false;
	}
	if (glfwGetKey(window, GLFW_KEY_A) != GLFW_RELEASE || glfwGetKey(window, GLFW_KEY_LEFT) != GLFW_RELEASE) {
		this->moveLeft = true;
	}
	else {
		this->moveLeft = false;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) != GLFW_RELEASE) {
		this->moveUp=true;
	}
	else {
		this->moveUp = false;
	}
	if (glfwGetKey(window, GLFW_KEY_E) != GLFW_RELEASE) {
		this->moveDown=true;
	}
	else {
		this->moveDown = false;
	}
	
}

void FirstPersonControls::OnResize(GLFWwindow* window, int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	this->camera->aspect = float(w)/h;
	this->camera->updateProjectionMatrix();
	this->viewHalfX = float(w) / 2;
	this->viewHalfY = float(h) / 2;
	std::cout << "窗口大小改变" << std::endl;
}

void FirstPersonControls::glfw_cursor_pos_callback(GLFWwindow* window, double x, double y) {
	this->pointerX = x - this->viewHalfX;
	this->pointerY = y - this->viewHalfY;
}
void FirstPersonControls::glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			
			std::cout << this->pointerX << std::endl;
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			
		}
	}
	if (action == GLFW_RELEASE)
	{
		
	}

}
void FirstPersonControls::glfw_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	isSroll = true;
	if (yoffset < 0)
		this->moveBackward=true;
	else {
		this->moveBackward = false;
	}
	if (yoffset > 0)
		this->moveForward=true;
	else {
		this->moveForward = false;
	}

}
void FirstPersonControls::glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key==GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if ((key == GLFW_KEY_W && action!= GLFW_RELEASE) || (key==GLFW_KEY_UP && action != GLFW_RELEASE))
	{
		this->moveForward = true;
	}
	else {
		this->moveForward = false;
	}
	if ((key == GLFW_KEY_S && action != GLFW_RELEASE) || (key == GLFW_KEY_DOWN && action != GLFW_RELEASE))
	{
		this->moveBackward = true;
	}
	else {
		this->moveBackward = false;
	}
	if ((key == GLFW_KEY_A && action != GLFW_RELEASE) || (key == GLFW_KEY_LEFT && action != GLFW_RELEASE))
	{
		this->moveLeft = true;
	}
	else {
		this->moveLeft = false;
	}
	if ((key == GLFW_KEY_D && action != GLFW_RELEASE) || (key == GLFW_KEY_RIGHT && action != GLFW_RELEASE))
	{
		this->moveRight = true;
	}
	else {
		this->moveRight = false;
	}
	if (key == GLFW_KEY_Q && action != GLFW_RELEASE )
	{
		this->moveUp = true;
	}
	else {
		this->moveUp = false;
	}
	if (key == GLFW_KEY_E && action != GLFW_RELEASE)
	{
		this->moveDown = true;
	}
	else {
		this->moveDown = false;
	}
}