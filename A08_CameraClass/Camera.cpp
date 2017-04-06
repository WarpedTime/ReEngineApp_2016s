#include "Camera.h"

/*
matrix4 m_m4Projection; //field of view, aspect ratio, near clipping, far clipping
matrix4 m_m4View; //origin, look at(normalized), up vector
vector3 v3Position;
vector3 v3LookAt;
vector3 v3Up;
quaternion qRotation;
*/

Camera::Camera()
{
	v3Position = vector3(0.0f, 0.0f, 15.0f);
	v3LookAt = vector3(0.0f, 0.0f, -3.0f);
	v3Up = vector3(0.0f, 1.0f, 0.0f);

	m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 100.0f);
	m4View = glm::lookAt(v3Position, v3LookAt, v3Up);
}
Camera::~Camera()
{
}

matrix4 Camera::GetView()
{
	return glm::lookAt(v3Position, v3LookAt, v3Up);
}

matrix4 Camera::GetProjection(bool bOrthographic)
{
	if(bOrthographic) return glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.01f, 1000.0f);
	else return glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 100.0f);
}

void Camera::SetPosition(vector3 v3Position)
{
	if (v3LookAt == v3Position) v3Position.x += 0.10f;
	this->v3Position = v3Position;
}

void Camera::SetTarget(vector3 v3Target)
{
	if (v3Target == v3Position) v3Target.x += 0.10f;
	this->v3LookAt = v3Target;
}

void Camera::SetUp(vector3 v3Up)
{
	this->v3Up = v3Up;
}

void Camera::MoveForward(float fIncrement) //move forward in direction of view
{
	//vector3 move = NormalizeV3(v3LookAt);
	vector4 temp = GetView() * (vector4(0.0,0.0,1.0f,0.0f) * fIncrement);
	vector3 move = vector3(temp.x,temp.y,temp.z);
	this->v3Position += move;
	this->v3LookAt += move;
}

void Camera::MoveSideways(float fIncrement) //strafe sideways from direction of view
{
	vector4 temp = GetView() * (vector4(1.0, 0.0, 0.0f, 0.0f) * fIncrement);
	vector3 move = vector3(temp.x, temp.y, temp.z);
	this->v3Position += move;
	this->v3LookAt += move;
}

void Camera::MoveVertical(float fIncrement) //x
{
	vector4 temp = GetView() * (vector4(0.0, 1.0, 0.0f, 0.0f) * fIncrement);
	vector3 move = vector3(temp.x, temp.y, temp.z);
	this->v3Position += move;
	this->v3LookAt += move;
}

void Camera::ChangePitch(float fIncrement) //y
{
	vector4 temp = GetView() * (vector4(0.0, 0.0, 1.0f, 0.0f) * fIncrement);
	vector3 move = vector3(temp.x, temp.y, temp.z);
	this->v3LookAt += move;
}

void Camera::ChangeRoll(float fIncrement) //z
{
	vector4 temp = GetView() * (vector4(1.0, 0.0, 0.0f, 0.0f) * fIncrement);
	vector3 move = vector3(temp.x, temp.y, temp.z);
	this->v3LookAt += move;
}

void Camera::ChangeYaw(float fIncrement) //y
{
	vector4 temp = GetView() * (vector4(0.0, 1.0, 0.0f, 0.0f) * fIncrement);
	vector3 move = vector3(temp.x, temp.y, temp.z);
	this->v3LookAt += move;
}

vector3 Camera::NormalizeV3(vector3 v)
{
	float mag = sqrt( (v.x*v.x) + (v.y*v.y) + (v.z*v.z) );
	return vector3( v.x/mag, v.y/mag, v.z/mag) ;
}
