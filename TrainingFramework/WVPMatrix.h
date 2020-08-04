#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
using namespace std;
class WVPMatrix
{
public:
	Matrix WVP; 
	Matrix S, R, T, W, Rx, Ry, Rz;
	Matrix V;
	Matrix P;
public:
	void Update(float deltaTime, Matrix projection, Matrix view);
	WVPMatrix();
	~WVPMatrix();
};

