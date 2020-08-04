#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include <vector>
#include "Model.h"
#include "Texture.h"
#include "WVPMatrix.h"
#include "Shaders.h"
using namespace std;
class Camera
{
	Vector3 pos;
	Vector3 target;
	Vector3 up;

	float angles;
	float speed ;
	float nearPlane, farPlane, fov , aspect;

	Matrix view;
	Matrix world;
	Matrix projection;
	
	Vector3 zaxis;
	Vector3 xaxis;
	Vector3 yaxis;
	
	int currentKey=0;
public:
	Vector3 getzaxis();
	Vector3 getxaxis();
	Vector3 getyaxis();

	Matrix setView();
	Matrix setWorld();
	Matrix setProjection();

	void foward(float deltaTime);
	void backward(float deltaTime);
	void left(float deltaTime);
	void right(float deltaTime);

	Matrix RotationMatrixAroundY(float deltaTime);
	Matrix RotationMatrixAroundX(float deltaTime);

	void rotationLeft(float deltaTime);
	void rotationRight(float deltaTime);
	void rotationUp(float deltaTime);
	void rotationDown(float deltaTime);

	void update(float deltaTime);
	int keyPressed(unsigned char key, bool bIsPressed);
	//void calculationMatrix();
	Camera(float * input);
	~Camera();
};

