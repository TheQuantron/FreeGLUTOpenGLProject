#include "Camera.h"
#include "Structures.h"
#include <math.h>

//Camera Constructor initialisaion
Camera::Camera()
{
	rotation = .0f;
	eye.x = .0f; eye.y = .0f; eye.z = 5.0f;
	centre.x = .0f; centre.y = .0f; centre.z = .0f;
	up.x = .0f; up.y = 1.0f; up.z = .0f;
}

void Camera::AngToAxis(const Vector3 angles, Vector3& roll, Vector3& yaw, Vector3& pitch)
{
	const float DEG2GRAD = acos(-1) / 180.0f;
	float sx, sy, sz, cx, cy, cz, theta;

	//Roll axis - Forward
	theta = angles.z * DEG2GRAD;
	sz = sin(theta);
	cz = cos(theta);

	//Yaw axis - Up
	theta = angles.y * DEG2GRAD;
	sy = sin(theta);
	cy = cos(theta);

	//Pitch axis - Left
	theta = angles.x * DEG2GRAD;
	sx = sin(theta);
	cx = cos(theta);

	//Forward axis
	roll.x = sy;
	roll.y = -sx * cy;
	roll.z = cx * cy;

	//Up axis
	yaw.x = -cy * sz;
	yaw.y = -sx * sy * sz + cx * cz;
	yaw.z = cx * sy * sz + sx * cz;

	//Left axis
	pitch.x = cy * cz;
	pitch.y = sx * sy * cz + cx * sz;
	pitch.z = -cx * sy * cz + sx * sz;
}

//Camera standard Updated function
void Camera::Update()
{
	glLoadIdentity();
	gluLookAt(eye.x, eye.y, eye.z, centre.x, centre.y, centre.z, up.x, up.y, up.z);
}

//Camera destructor initliasation
Camera::~Camera() {}
