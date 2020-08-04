#include "stdafx.h"
#include "Model.h"




Model::Model(char * input)
{
	FILE * fp = fopen(input, "r");
	if (fp == NULL) {
		printf("Loi mo file");
		exit(1);
	}
	fscanf(fp, "NrVertices: %d\n", &NrVertices);
	//triangle data (heap)
	verticesData = new Vertex[NrVertices];
	for (int i = 0; i < NrVertices; i++) {
		fscanf(fp, "   %*d. pos:[%f, %f, %f]; norm:[%*f, %*f, %*f]; binorm:[%*f, %*f, %*f]; tgt:[%*f, %*f, %*f]; uv:[%f, %f];\n",
			&verticesData[i].pos.x, &verticesData[i].pos.y, &verticesData[i].pos.z,
			&verticesData[i].uv.x, &verticesData[i].uv.y);
	}

	fscanf(fp, "NrIndices: %d\n", &NrIndices);
	inticesData = new GLuint[NrIndices];
	for (int i = 0; i < NrIndices; i = i + 3) {
		fscanf(fp, " %*d.    %d,    %d,    %d\n", &inticesData[i], &inticesData[i + 1], &inticesData[i + 2]);
	}
	/*verticesData[0].pos.x = -1.0f;  verticesData[0].pos.y = 1.0f;  verticesData[0].pos.z = 0.0f;
	verticesData[1].pos.x = -1.0f;  verticesData[1].pos.y = -1.0f;  verticesData[1].pos.z = 0.0f;
	verticesData[2].pos.x = 1.0f;  verticesData[2].pos.y = -1.0f;  verticesData[2].pos.z = 0.0f;
	verticesData[3].pos.x = 1.0f;  verticesData[3].pos.y = 1.0f;  verticesData[3].pos.z = 0.0f;

	verticesData[0].uv.x = 0.0f;  verticesData[0].uv.y = 1.0f;
	verticesData[1].uv.x = 0.0f;  verticesData[1].uv.y = 0.0f;
	verticesData[2].uv.x = 1.0f;  verticesData[2].uv.y = 0.0f;
	verticesData[3].uv.x = 1.0f;  verticesData[3].uv.y = 1.0f;

	verticesData[0].color.x = 1.0f;  verticesData[0].color.y = 0.0f;  verticesData[0].color.z = 0.0f;
	verticesData[1].color.x = 0.0f;  verticesData[1].color.y = 1.0f;  verticesData[1].color.z = 0.0f;
	verticesData[2].color.x = 0.0f;  verticesData[2].color.y = 0.0f;  verticesData[2].color.z = 1.0f; */
}

Model::~Model()
{
}


