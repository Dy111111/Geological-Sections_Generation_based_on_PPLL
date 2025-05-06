#include"TrackballControls.h"
TrackballControls::TrackballControls(Camera* camera, GLFWwindow* window) :
	camera(camera),
	window(window)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	screenHeight = height;
	screenWidth = width;
	target0 = target;
	position0 = camera->position;
	up0 = camera->up;
	zoom0 = camera->zoom;
};
void TrackballControls::update() {
	glm::vec3 lastpos = camera->position;
	_eye = camera->position - target;
	if (!noRotate) {
		rotateCamera();
	}
	if (!noZoom) {
		zoomCamera();
	}
	if (!noPan) {
		panCamera();
	}
	camera->position = target + _eye;
	checkDistance();
	camera->lookAt(target);
	
	double distanceSquare = pow(lastPosition.x - camera->position.x, 2) + pow(lastPosition.y - camera->position.y, 2) + pow(lastPosition.z - camera->position.z, 2);
	if (distanceSquare > EPS)
	{
		lastPosition = camera->position;
	}
}



void TrackballControls::glfw_keyboard_input_callback(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) != GLFW_RELEASE || glfwGetKey(window, GLFW_KEY_UP) != GLFW_RELEASE)
	{
		
	}
	else {
		
	}
	if (glfwGetKey(window, GLFW_KEY_S) != GLFW_RELEASE || glfwGetKey(window, GLFW_KEY_DOWN) != GLFW_RELEASE)
	{
		
	}
	else {
		
	}
	if (glfwGetKey(window, GLFW_KEY_D) != GLFW_RELEASE || glfwGetKey(window, GLFW_KEY_RIGHT) != GLFW_RELEASE) {
		
	}
	else {
		
	}
	if (glfwGetKey(window, GLFW_KEY_A) != GLFW_RELEASE || glfwGetKey(window, GLFW_KEY_LEFT) != GLFW_RELEASE) {
		
	}
	else {
		
	}
	if (glfwGetKey(window, GLFW_KEY_Q) != GLFW_RELEASE) {
		
	}
	else {
		
	}
	if (glfwGetKey(window, GLFW_KEY_E) != GLFW_RELEASE) {
		
	}
	else {
		
	}

}

void TrackballControls::OnResize(GLFWwindow* window, int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	this->camera->aspect = float(w) / h;
	this->camera->updateProjectionMatrix();
	screenHeight = h;
	screenWidth = w;
	std::cout << "窗口大小改变" << std::endl;
}

void TrackballControls::glfw_cursor_pos_callback(GLFWwindow* window, double x, double y) {
	STATE state = (_keyState != STATE::NONE) ? _keyState : _state;
	if (state == STATE::ROTATE && !noRotate) {

		_movePrev=_moveCurr;
		_moveCurr=getMouseOnCircle(x, y);

	}
	else if (state == STATE::ZOOM && !noZoom) {

		_zoomEnd=getMouseOnScreen(x, y);

	}
	else if (state == STATE::PAN && !noPan) {

		_panEnd=getMouseOnScreen(x, y);

	}
}
void TrackballControls::glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			_state = STATE::ROTATE;
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			_state = STATE::PAN;
		}
		else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {//?
			_state = STATE::ZOOM;
		}
	}
	if (action == GLFW_RELEASE)
	{
		_state = STATE::NONE;
	}
	STATE state= (_keyState !=STATE::NONE) ? _keyState : _state;
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	if (state ==STATE::ROTATE && !noRotate) {
		
		_moveCurr=getMouseOnCircle(x,y);
		_movePrev=_moveCurr;

	}
	else if (state == STATE::ZOOM && !noZoom) {

		_zoomStart=getMouseOnScreen(x ,y);
		_zoomEnd=_zoomStart;

	}
	else if (state ==STATE::PAN && !noPan) {

		_panStart=getMouseOnScreen(x, y);
		_panEnd=_panStart;

	}

}
glm::vec2 TrackballControls::getMouseOnScreen(double x, double y) {
	return glm::vec2(x / screenWidth, y/ screenHeight);
}

glm::vec2 TrackballControls::getMouseOnCircle(double x, double y) {
	double xpos = (x - screenWidth * 0.5) / (screenWidth * 0.5);
	double ypos = (screenHeight + 2 * (-y)) / screenWidth;
	return glm::vec2(xpos, ypos);
}

void TrackballControls::rotateCamera() {
	glm::vec3 axis;
	glm::quat quaternion;
	glm::vec3 eyeDirection;
	glm::vec3 objectUpDirection;
	glm::vec3 objectSidewayDirection;
	glm::vec3 moveDirection=glm::vec3(_moveCurr.x - _movePrev.x, _moveCurr.y - _movePrev.y, 0);
	float angle = glm::length(moveDirection);
	if (angle) {
		_eye = camera->position-target;//target
		eyeDirection = glm::normalize(_eye);
		objectUpDirection = glm::normalize(camera->up);
		objectSidewayDirection = glm::normalize(glm::cross(objectUpDirection, eyeDirection));
		objectUpDirection = objectUpDirection * (_moveCurr.y - _movePrev.y);
		objectSidewayDirection = objectSidewayDirection * (_moveCurr.x - _movePrev.x);
		moveDirection = objectUpDirection + objectSidewayDirection;
		axis = glm::normalize(glm::cross(moveDirection, _eye));
		angle *= rotateSpeed;
		quaternion= glm::angleAxis(angle, axis);
		_eye = glm::rotate(quaternion,_eye);//?
		camera->up = glm::rotate(quaternion, camera->up);
		_lastAxis = axis;
		_lastAngle = angle;
	}
	else if (!staticMoving && _lastAngle) {
		_lastAngle *= sqrt(1.0 - dynamicDampingFactor);
		_eye = camera->position - target;
		quaternion= glm::angleAxis(_lastAngle, _lastAxis);
		_eye = glm::rotate(quaternion, _eye);
		camera->up = glm::rotate(quaternion, camera->up);
	}
	_movePrev = _moveCurr;
}

void TrackballControls::zoomCamera() {
	float factor;
	factor=1.0+ (_zoomEnd.y - _zoomStart.y) * zoomSpeed;
	_eye = _eye * factor;
	if (staticMoving) {

		_zoomStart=_zoomEnd;

	}
	else {

		_zoomStart.y += (_zoomEnd.y - _zoomStart.y) * dynamicDampingFactor;

	}
}

void TrackballControls::panCamera() {
	glm::vec2 mouseChange;
	glm::vec3 objectUp;
	glm::vec3 pan;
	mouseChange = _panEnd - _panStart;
	float len = sqrt(mouseChange.x * mouseChange.x + mouseChange.y * mouseChange.y);
	if (len) {
		mouseChange = mouseChange * sqrt(_eye.x * _eye.x + _eye.y * _eye.y + _eye.z * _eye.z) * panSpeed;
	}
	pan = glm::normalize(glm::cross(_eye, camera->up)) * mouseChange.x;
	pan = pan + glm::normalize(camera->up) * mouseChange.y;
	camera->position = camera->position + pan;
	target = target + pan;
	if (staticMoving) {
		_panStart = _panEnd;
	}
	else {
		mouseChange = _panEnd - _panStart;
		_panStart = _panStart + mouseChange * dynamicDampingFactor;
	}

}

void TrackballControls::checkDistance() {
	if (!noZoom || !noPan) {

		if (_eye.x*_eye.x+ _eye.y * _eye.y+ _eye.z * _eye.z > maxDistance * maxDistance) {

			camera->position= target+ glm::normalize(_eye)*maxDistance;
			_zoomStart=_zoomEnd;

		}

		if (_eye.x * _eye.x + _eye.y * _eye.y + _eye.z * _eye.z < minDistance * minDistance) {

			camera->position = target + glm::normalize(_eye) * minDistance;
			_zoomStart = _zoomEnd;

		}

	}
}

void TrackballControls::reset() {
	_state = STATE::NONE;
	_keyState = STATE::NONE;
	target = target0;
	camera->position = position0;
	camera->up = up0;
	camera->zoom = zoom0;
	camera->updateProjectionMatrix();
	_eye = camera->position - target;
	camera->lookAt(target);
	lastPosition = camera->position;
	lastZoom = camera->zoom;
}
void TrackballControls::glfw_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	if (noZoom ==true) return;
	_zoomStart.y -= yoffset * 0.025;
}
void TrackballControls::glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if ((key == GLFW_KEY_W && action != GLFW_RELEASE) || (key == GLFW_KEY_UP && action != GLFW_RELEASE))
	{
		
	}
	else {
		
	}
	if ((key == GLFW_KEY_S && action != GLFW_RELEASE) || (key == GLFW_KEY_DOWN && action != GLFW_RELEASE))
	{
		
	}
	else {
		
	}
	if ((key == GLFW_KEY_A && action != GLFW_RELEASE) || (key == GLFW_KEY_LEFT && action != GLFW_RELEASE))
	{
		
	}
	else {
		
	}
	if ((key == GLFW_KEY_D && action != GLFW_RELEASE) || (key == GLFW_KEY_RIGHT && action != GLFW_RELEASE))
	{
		
	}
	else {
		
	}
	if (key == GLFW_KEY_Q && action != GLFW_RELEASE)
	{
		
	}
	else {
		
	}
	if (key == GLFW_KEY_E && action != GLFW_RELEASE)
	{
		
	}
	else {
	
	}
}