#include "stdafx.h"
#include "Camera.h"

#define R_UP	1<<8
#define R_DOWN	1<<1
#define R_LEFT	1<<2
#define R_RIGHT 1<<3
#define FW		1<<4
#define BW		1<<5
#define L		1<<6
#define R		1<<7

Vector3 Camera::getzaxis()
{
	zaxis = (pos - target).Normalize();
	return zaxis;
}

Vector3 Camera::getxaxis()
{
	xaxis = (up.Cross(zaxis)).Normalize();
	return xaxis;
}

Vector3 Camera::getyaxis()
{
	yaxis = (zaxis.Cross(xaxis)).Normalize();
	return yaxis;
}


Matrix Camera::setView()
{
	xaxis = getxaxis();
	yaxis = getyaxis();
	zaxis = getzaxis();

	this->view.m[0][0] = xaxis.x;				  
	this->view.m[0][1] = yaxis.x;				 
	this->view.m[0][2] = zaxis.x;				  
	this->view.m[0][3] = 0;

	this->view.m[1][0] = xaxis.y;				  
	this->view.m[1][1] = yaxis.y;				  
	this->view.m[1][2] = zaxis.y;				  
	this->view.m[1][3] = 0;

	this->view.m[2][0] = xaxis.z;				 
	this->view.m[2][1] = yaxis.z;				  
	this->view.m[2][2] = zaxis.z;				  
	this->view.m[2][3] = 0;

	this->view.m[3][0] = -this->pos.Dot(xaxis);   
	this->view.m[3][1] = -this->pos.Dot(yaxis); 
	this->view.m[3][2] = -this->pos.Dot(zaxis); 
	this->view.m[3][3] = 1;

	return this->view;
}

Matrix Camera::setWorld()
{
	xaxis = getxaxis();
	yaxis = getyaxis();
	zaxis = getzaxis();

	this->world.m[0][0] = xaxis.x; 
	this->world.m[0][1] = xaxis.y; 
	this->world.m[0][2] = xaxis.z; 
	this->world.m[0][3] = 0;

	this->world.m[1][0] = yaxis.x; 
	this->world.m[1][1] = yaxis.y; 
	this->world.m[1][2] = yaxis.z; 
	this->world.m[1][3] = 0;

	this->world.m[2][0] = zaxis.x; 
	this->world.m[2][1] = zaxis.y; 
	this->world.m[2][2] = zaxis.z; 
	this->world.m[2][3] = 0;

	this->world.m[3][0] = pos.x*xaxis.x+pos.y*yaxis.x+pos.z*zaxis.x; 
	this->world.m[3][1] = pos.x*xaxis.y+pos.y*yaxis.y+pos.z*zaxis.y; 
	this->world.m[3][2] = pos.x*xaxis.z+pos.y*yaxis.z+pos.z*zaxis.z; 
	this->world.m[3][3] = 1;

	return this->world;
}

Matrix Camera::setProjection()
{
	return projection;
}

void Camera::foward(float deltaTime)
{
	Vector3 deltaMove = -getzaxis()*deltaTime*speed;
	pos += deltaMove;
	target += deltaMove;
}

void Camera::backward(float deltaTime)
{
	Vector3 deltaMove = -getzaxis()*deltaTime*speed;
	pos -= deltaMove;
	target -= deltaMove;
}

void Camera::left(float deltaTime)
{
	Vector3 deltaMove = -getxaxis()*deltaTime*speed;
	pos += deltaMove;
	target += deltaMove;
}

void Camera::right(float deltaTime)
{
	Vector3 deltaMove = -getxaxis()*deltaTime*speed;
	pos -= deltaMove;
	target -= deltaMove;
}

Matrix Camera::RotationMatrixAroundY(float angles)
{
	Matrix rotation;
	Vector4 rotationaxis = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	rotationaxis = rotationaxis*setView();
	return rotation.SetRotationAngleAxis(angles, rotationaxis.x, rotationaxis.y, rotationaxis.z);
}

Matrix Camera::RotationMatrixAroundX(float angles)
{
	Matrix rotation;
	Vector4 rotationaxis = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
	rotationaxis = rotationaxis*setView();
	return rotation.SetRotationAngleAxis(angles, rotationaxis.x, rotationaxis.y, rotationaxis.z);
}

void Camera::rotationLeft(float deltaTime)
{
	Vector4 localTarget = Vector4(0, 0, -(pos - target).Length(), 1);
	Vector4 localNewTarget = localTarget*RotationMatrixAroundY(deltaTime*speed);
	Vector4 worldNewTarget = localNewTarget*setWorld();
	target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}

void Camera::rotationRight(float deltaTime)
{
	Vector4 localTarget = Vector4(0, 0, -(pos - target).Length(), 1);
	Vector4 localNewTarget = localTarget*RotationMatrixAroundY(-deltaTime*speed);
	Vector4 worldNewTarget = localNewTarget*setWorld();
	target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}

void Camera::rotationUp(float deltaTime)
{
	Vector4 localTarget = Vector4(0, 0, -(pos - target).Length(), 1);
	Vector4 localNewTarget = localTarget*RotationMatrixAroundX(-deltaTime*speed);
	Vector4 worldNewTarget = localNewTarget*setWorld();
	target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}

void Camera::rotationDown(float deltaTime)
{
	Vector4 localTarget = Vector4(0, 0, -(pos - target).Length(), 1);
	Vector4 localNewTarget = localTarget*RotationMatrixAroundX(deltaTime*speed);
	Vector4 worldNewTarget = localNewTarget*setWorld();
	target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}

void Camera::update(float deltaTime)
{
	if (currentKey == R_UP) {
		rotationUp(deltaTime);
	}
	else if (currentKey == R_DOWN) {
		rotationDown(deltaTime);
	}
	else if (currentKey == R_LEFT) {
		rotationLeft(deltaTime);
	}
	else if (currentKey == R_RIGHT) {
		rotationRight(deltaTime);
	}
	else if (currentKey == FW) {
		foward(deltaTime);
	}
	else if (currentKey == L) {
		left(deltaTime);
	}
	else if (currentKey == R) {
		right(deltaTime);
	}
	else if (currentKey == BW) {
		backward(deltaTime);
	}
}

int Camera::keyPressed(unsigned char key, bool bIsPressed)
{
	if (key == VK_UP) {
		if (bIsPressed) {
			currentKey = R_UP;
		}
		else {
			currentKey = 0;
		}
	}
	else if(key== VK_DOWN) {
		if (bIsPressed) {
			currentKey = R_DOWN;
		}
		else {
			currentKey = 0;
		}
	}
	else if (key== VK_LEFT) {
		if (bIsPressed) {
			currentKey = R_LEFT;
		}
		else {
			currentKey = 0;
		}
	}
	else if (key == VK_RIGHT) {
		if (bIsPressed) {
			currentKey = R_RIGHT;
		}
		else {
			currentKey = 0;
		}
	}
	else if (key == 'A' | key == 'a') {
		if (bIsPressed) {
			currentKey = L;
		}
		else {
			currentKey = 0;
		}
	}
	else if (key == 'D' | key == 'd') {
		if (bIsPressed) {
			currentKey = R;
		}
		else {
			currentKey = 0;
		}
	}
	else if (key == 'W' | key == 'w') {
		if (bIsPressed) {
			currentKey = FW;
		}
		else {
			currentKey = 0;
		}
	}
	else if (key == 'S' | key == 's') {
		if (bIsPressed) {
			currentKey = BW;
		}
		else {
			currentKey = 0;
		}
	}
	return currentKey;
}


Camera::Camera(float * input)
{
	pos = Vector3(0.0f, 0.0f, -3.0f);
	target = Vector3(0.0f, 0.0f, 0.0f);
	up = Vector3(0.0f, 1.0f, 0.0f);

	speed = input[3];
	nearPlane = input[0]; 
	farPlane = input[1]; 
	fov = input[2]; 
	aspect = Globals::screenWidth / Globals::screenHeight;

	projection.SetPerspective(fov, aspect, nearPlane, farPlane);

}


Camera::~Camera()
{
}
