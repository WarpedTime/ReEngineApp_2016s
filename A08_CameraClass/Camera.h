#pragma once
#ifndef __CAMERA_H_
#define __CAMERA_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
//#include <chrono>

#include "RE\ReEng.h"
using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

class Camera
{
public:
	matrix4 m4Projection; //field of view, aspect ratio, near clipping, far clipping
	matrix4 m4View; //origin, look at(normalized), up vector
	vector3 v3Position;
	vector3 v3LookAt;
	vector3 v3Up;
	quaternion qRotation;

	matrix4 GetView();
	matrix4 GetProjection(bool bOrthographic);

	void SetPosition(vector3 v3Position);
	void SetTarget(vector3 v3Target);
	void SetUp(vector3 v3Up);

	void MoveForward(float fIncrement);
	void MoveSideways(float fIncrement);
	void MoveVertical(float fIncrement);

	void ChangePitch(float fIncrement);
	void ChangeRoll(float fIncrement);
	void ChangeYaw(float fIncrement);
	
	vector3 NormalizeV3(vector3 v);

	Camera();
	~Camera();
};

#endif
