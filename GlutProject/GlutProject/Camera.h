#pragma once
#include "Structures.h"

class Camera
{
private:
	float rotation;

public:
	Camera();
	~Camera();
	void Update();
	void AngToAxis(const Vector3 angles, Vector3& roll, Vector3& yaw, Vector3& pitch);

	Vector3 eye, centre, up;
};
