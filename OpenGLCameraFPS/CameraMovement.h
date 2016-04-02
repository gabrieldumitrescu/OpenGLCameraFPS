/*CameraMovement class*/

#ifndef CAMERA_MOVEMENT_H
#define CAMERA_MOVEMENT_H


//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//Directions the camera can move
enum CamDir
{
	CAM_FW, CAM_BW, CAM_LEFT, CAM_RIGHT, DIR_SIZE
};

// Window dimensions
const GLuint WIDTH = 1024, HEIGHT = 768;

/* Go to the next direction
!!! WARNING No bounds check
*/
CamDir& operator++(CamDir& dir);


class CameraMovement{
public:
	CameraMovement();

	void moveCamera();
	

	glm::mat4& getView();

	void mouseUpdate(double posx, double posy);

	void fovUpdate(double xoffset, double yoffset);

	GLfloat getFOV();

	GLboolean getIsMoving(CamDir dir);

	void setIsMoving(CamDir dir, GLboolean flag = true);

	void setCamSpeed(GLfloat speed);

private:
	glm::vec3 m_camPos, m_camFront, m_camUp;
	glm::mat4 m_view;
	GLfloat m_camSpeed;
	GLfloat m_mouseSensitivity;
	GLfloat m_lastX, m_lastY, pitch, yaw;
	GLboolean m_firstMouse;
	GLboolean m_camIsMoving[DIR_SIZE];
	GLfloat m_fov;
};


#endif //CAMERA_MOVEMENT_H