#ifndef CAMERA_H_
#define CAMERA_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Camera
{
public:
	Camera(vec3 position, vec3 worldUp, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat turnSpeed);
	void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange);
	mat4 calculateViewMatrix();
	~Camera();

private:
	vec3 m_position;
	vec3 m_front;
	vec3 m_up;
	vec3 m_right;
	vec3 m_worldUp;
	
	GLfloat m_yaw;
	GLfloat m_pitch; // you could also have roll here!
	
	GLfloat m_movementSpeed;
	GLfloat m_turnSpeed;
	
	void update();
};

#endif
