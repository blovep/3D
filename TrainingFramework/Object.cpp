#include "stdafx.h"
#include "Object.h"




void Object::loadCube(char * resource0, char * resource1, char * resource2, char * resource3, char * resource4, char * resource5)
{
	myTexture = new Texture();
	myTexture->loadCube(resource0, resource1, resource2, resource3, resource4, resource5);
}

void Object::loadModel(char * model)
{
	myModel = new Model(model);
	//buffer object
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, myModel->NrVertices * sizeof(Vertex), myModel->verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, myModel->NrIndices * sizeof(GLuint), myModel->inticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Object::loadTexture(char * texture)
{
	myTexture = new Texture(texture);
}


void Object::creatShader(char * vs, char * fs)
{
	//creation of shaders and program 
	Shaders * a = new Shaders();
	int i = a->Init(vs, fs);
	printf("\n\n\n            %d               \n", i);
	if(i==0) 
	myShaders = a;
	return;
}
void Object::Update(float deltaTime, Matrix projection, Matrix view)
{
	myWVP->Update(deltaTime, projection, view);
}

void Object::Render()
{
	glUseProgram(myShaders->program);

	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	if (cube)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, myTexture->textureId);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, myTexture->textureId);
	}

	if (myShaders->positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders->positionAttribute);
		glVertexAttribPointer(myShaders->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	/*if (myShaders.colorAttribute != -1)
	{
	glEnableVertexAttribArray(myShaders.colorAttribute);
	glVertexAttribPointer(myShaders.colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0+sizeof(Vector3));
	}*/
	if (myShaders->uvAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders->uvAttribute);
		glVertexAttribPointer(myShaders->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3));
	}
	if (myShaders->matrixId != -1)
	{
		glEnableVertexAttribArray(myShaders->matrixId);
		glUniformMatrix4fv(myShaders->matrixId, 1, GL_FALSE, (float*)&myWVP->WVP.m);
	}
	if (myShaders->iTextureLoc != -1) {
		glUniform1i(myShaders->iTextureLoc, 0);
	}
	if (myShaders->iCubeLoc != -1) {
		glUniform1i(myShaders->iCubeLoc, 0);
	}
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, myModel->NrIndices, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	if (cube)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
}

Object::Object(int * id, float * a, int * texture, int * cube)
{

	this->ID = id[0];
	this->modelID = id[1];
	this->textureID = texture;
	this->cubeID = cube;
	this->shaderID = id[4];

	this->myWVP = new WVPMatrix();
	this->myWVP->T.SetTranslation(a[0], a[1], a[2]); 
	this->myWVP->Rx.SetRotationX(a[3]);
	this->myWVP->Ry.SetRotationY(a[4]);
	this->myWVP->Rz.SetRotationZ(a[5]);
	this->myWVP->S.SetScale(a[6], a[7], a[8]);

	this->myWVP->R = this->myWVP->Rx*this->myWVP->Ry*this->myWVP->Rz;
	this->myWVP->W = this->myWVP->S*this->myWVP->R*this->myWVP->T;
	this->myWVP->WVP = this->myWVP->W*this->myWVP->V*this->myWVP->P;
}

Object::~Object()
{
	glDeleteBuffers(1, &vboId);
	glDeleteBuffers(1, &iboId);
}
