#include "stdafx.h"
#include "ResourceManager.h"
ResourceManager * ResourceManager::ms_pInstance = NULL;


Object * ResourceManager::Init(char * file, int * input, float * a, int * texture, int * cube)
{
	Object * tmp = new Object(input, a, texture, cube);
	if (input[3] != 0) {
		tmp->cube = true;
	}
	FILE * fp = fopen(file, "r");
	int modelID, textureID, cubeID, sharderID;

	if (fp == NULL) {
		printf("Loi mo file\n");
		exit(1);
	}
	fscanf(fp, "#Models: %d\n", &modelID);
	for (int i = 0; i < modelID; i++) {
		int id;
		char resource[50];
		fscanf(fp, "ID %d\nFILE %s\n", &id, resource);
		printf("%s\n", resource);
		if (id == tmp->modelID) {
			tmp->loadModel(resource);
		}
	}

	fscanf(fp, "#2D Textures: %d\n", &textureID);
	printf("%d\n", textureID);
	for (int i = 0; i < textureID; i++) {
		int id;
		char resource[50];
		fscanf(fp, "ID %d\nFILE %s\nTILING %*s\n", &id, &resource);
		for (int j = 0; j < input[2]; j++) {
			printf("%d - %d;", id, tmp->textureID[j]);
			if (id == tmp->textureID[j]) {
				tmp->loadTexture(resource);
			}
		}
	}

	fscanf(fp, "#Cube Textures: %d\n", &cubeID);
	printf("%d\n", cubeID);
	for (int i = 0; i < cubeID; i++) {
		int id;
		char resource0[50], resource1[50], resource2[50], resource3[50], resource4[50], resource5[50];
		fscanf(fp, "ID %d\nFILE %s\nFILE %s\nFILE %s\nFILE %s\nFILE %s\nFILE %s\n", &id, resource0, resource1, resource2, resource3, resource4, resource5);
		for (int j = 0; j < input[3]; j++) {
			if (id == tmp->cubeID[j]) {
				tmp->loadCube(resource0, resource1, resource2, resource3, resource4, resource5);
			}
		}
	}

	fscanf(fp, "#Sharders: %d\n", &sharderID);
	for (int i = 0; i < sharderID; i++) {
		int id;
		char resource[50];
		char resource1[50];
		fscanf(fp, "ID %d\nVS %s\nFS %s\nSTATE %*s\n", &id, resource, resource1);
		if (id == tmp->shaderID) {
			tmp->creatShader(resource, resource1);
			printf("%d %d %s %s\n", id, tmp->shaderID, resource, resource1);
		}
	}
	return tmp;
}
