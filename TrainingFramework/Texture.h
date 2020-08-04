#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include <vector>
using namespace std;
class Texture
{
public:
	GLuint textureId;
	Texture(char* input);
	void loadCube(char * resource0, char * resource1, char * resource2, char * resource3, char * resource4, char * resource5);
	~Texture();
	Texture();
};

