/*CameraMovement class impl.*/


#include "CameraMovement.h"

CamDir& operator++(CamDir& dir)
{
	dir = CamDir((int)dir + 1);
	return dir;
}


CameraMovement::CameraMovement() :
m_camSpeed(0.1f),
m_camPos(glm::vec3(0.0f, 0.0f, 3.0f)),
m_camFront(glm::vec3(0.0f, 0.0f, -1.0f)),
m_camUp(glm::vec3(0.0f, 1.0f, 0.0f)),
m_lastX((float)WIDTH / 2.0f),
m_lastY((float)HEIGHT / 2.0f),
pitch(0.0f),
yaw(-90.0f),
m_mouseSensitivity(0.05f),
m_firstMouse(true),
m_fov(45.0f)
{

	for (CamDir d = CAM_FW; d < DIR_SIZE; ++d)
		m_camIsMoving[d] = false;
	m_view = glm::lookAt(m_camPos, m_camPos + m_camFront, m_camUp);
}

void CameraMovement::moveCamera(){
	if (m_camIsMoving[CAM_FW])
		m_camPos += m_camFront * m_camSpeed;
	if (m_camIsMoving[CAM_BW])
		m_camPos -= m_camFront*m_camSpeed;
	if (m_camIsMoving[CAM_LEFT])
		m_camPos -= glm::normalize(glm::cross(m_camFront, m_camUp))*m_camSpeed;
	if (m_camIsMoving[CAM_RIGHT])
		m_camPos += glm::normalize(glm::cross(m_camFront, m_camUp))*m_camSpeed;
	m_view = glm::lookAt(m_camPos, m_camPos + m_camFront, m_camUp);
}

void CameraMovement::mouseUpdate(double posx, double posy)
{
	if (m_firstMouse)
	{
		m_lastX = (GLfloat)posx;
		m_lastY = (GLfloat)posy;
		m_firstMouse = false;
	}
	GLfloat xoffset = posx - m_lastX;
	GLfloat yoffset = m_lastY - posy;//Invert y axis
	m_lastX = posx;
	m_lastY = posy;
	xoffset *= m_mouseSensitivity;
	yoffset *= m_mouseSensitivity;

	yaw += xoffset;
	pitch += yoffset;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	m_camFront.x = cos(glm::radians(pitch))*cos(glm::radians(yaw));
	m_camFront.y = sin(glm::radians(pitch));
	m_camFront.z = cos(glm::radians(pitch))*sin(glm::radians(yaw));
	m_camFront = glm::normalize(m_camFront);
	m_view = glm::lookAt(m_camPos, m_camPos + m_camFront, m_camUp);
}

glm::mat4& CameraMovement::getView(){
	return m_view;
}

void CameraMovement::fovUpdate(double xoffset, double yoffset)
{

	m_fov -= yoffset;
	if (m_fov <= 1.0f)
	{
		m_fov = 1.0f;
		return;
	}
	if (m_fov >= 45.0f)
	{
		m_fov = 45.0f;
		return;
	}

}

GLfloat CameraMovement::getFOV()
{
	return m_fov;
}

GLboolean CameraMovement::getIsMoving(CamDir dir)
{
	return m_camIsMoving[dir];
}

void CameraMovement::setIsMoving(CamDir dir, GLboolean flag)
{
	m_camIsMoving[dir] = flag;
}

void CameraMovement::setCamSpeed(GLfloat speed)
{
	m_camSpeed = speed;
}
