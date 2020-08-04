#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include <vector>
using namespace std;
class Model
{
public:
	int NrVertices, NrIndices;
	Vertex * verticesData;
	GLuint * inticesData;
	Model(char*input);
	~Model();
};

