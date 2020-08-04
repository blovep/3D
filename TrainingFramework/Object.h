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
class Object
{
	GLuint vboId;
	GLuint iboId;
	Shaders *myShaders;
	Model *myModel;
	Texture *myTexture;
	
public:
	int ID, modelID, * textureID, * cubeID, shaderID;
	bool cube = false;
	WVPMatrix *myWVP;
	void loadCube(char * resource0, char * resource1, char * resource2, char * resource3, char * resource4, char * resource5);
	void loadModel(char * model);
	void loadTexture(char * texture);
	void creatShader(char * vs, char * fs);
	void Update(float deltaTime, Matrix projection, Matrix view);
	void Render();
	Object(int * id, float * a, int * texture, int * cube);
	~Object();
};

