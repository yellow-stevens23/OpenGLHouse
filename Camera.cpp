#include "Camera.h"


Camera::Camera(vec3 position, vec3 worldUp, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat turnSpeed)
{
	m_position = position;
	m_worldUp = worldUp;
	m_yaw = yaw;
	m_pitch = pitch;
	m_front = vec3(0.0f, 0.0f, -1.0f); // we are moving the camera back a bit at the start
	
	m_movementSpeed = moveSpeed;
	m_turnSpeed = turnSpeed;
	
	update();
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = m_movementSpeed * deltaTime;	
	
	if (keys[GLFW_KEY_W])
	{
		m_position += m_front * velocity;
	}
	
	if (keys[GLFW_KEY_S])
	{
		m_position -= m_front * velocity;
	}
	
	if (keys[GLFW_KEY_A])
	{
		m_position -= m_right * velocity;
	}
	
	if (keys[GLFW_KEY_D])
	{
		 m_position += m_right * velocity;
	}
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= m_turnSpeed;
	yChange *= m_turnSpeed;

	m_yaw += xChange;
	m_pitch += yChange;

	if (m_pitch > 89.0f)
	{
		m_pitch = 89.0f;
	}

	if (m_pitch < -89.0f)
	{
		m_pitch = -89.0f;
	}

	update();
}

mat4 Camera::calculateViewMatrix()
{
	return lookAt(m_position, m_position + m_front, m_up);  // you could look at the character in this case just forward
}

void Camera::update()
{
	m_front.x = cos(radians(m_yaw)) * cos(radians(m_pitch));
	m_front.y = sin(radians(m_pitch));
	m_front.z = sin(radians(m_yaw)) * cos(radians(m_pitch));
	m_front = normalize(m_front);
	
	m_right = normalize(cross(m_front, m_worldUp));
	m_up = normalize(cross(m_right, m_front));
}

Camera::~Camera()
{
}
