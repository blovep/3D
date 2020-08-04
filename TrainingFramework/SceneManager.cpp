#include "stdafx.h"
#include "SceneManager.h"

SceneManager * SceneManager::ms_pInstance = NULL;

void SceneManager::Update(float frameTime)
{
	myCamera->update(frameTime);
	Object *a;
	for (int i = 0; i < m_ListObject.size(); i++) {
		a = m_ListObject.at(i);
		a->Update(frameTime, myCamera->setProjection(), myCamera->setView());
	}
}

void SceneManager::Render()
{
	Object *a;
	for (int i = 0; i < m_ListObject.size(); i++) {
		a = m_ListObject.at(i);
		a->Render();
	}
}

void SceneManager::AddObject(Object * object)
{
	m_ListObject.push_back(object);
}

void SceneManager::Init(char * scene, char * resource)
{
	ResourceManager::CreateInstance();
	FILE * fp = fopen(scene, "r");
	if (fp == NULL) {
		printf("Loi mo file\n");
		exit(1);
	}
	int ID[5], object;
	int *  texture = NULL, * cube = NULL;
	float a[9], camera[4];
	char buff[20];

	if (fscanf(fp, "%s", buff) != EOF) {
		fscanf(fp, "%d\n\n", &object);
	}
	for (int i = 0; i < object; i++) {
		fscanf(fp, "ID %d\nMODEL %d\nTEXTURES %d\n", &ID[0], &ID[1], &ID[2]);
		printf("\n%d %d %d\n", ID[0], ID[1], ID[2]);
		if (ID[2] != 0) {
			texture = new int[ID[2]];
			for (int j = 0; j < ID[2]; j++) {
				fscanf(fp, "TEXTURE %d\n",&texture[j]);
				printf("%d", texture[j]);
			}
		}
		fscanf(fp, "CUBETEXTURES %d\n", &ID[3]);
		printf("\n%d\n", ID[3]);
		if (ID[3] != 0) {
			cube = new int[ID[3]];
			for (int j = 0; j < ID[3]; j++) {
				fscanf(fp, "CUBETEXT %d\n", &cube[j]);
				printf("%d", cube[j]);
			}
		}
		fscanf(fp, "SHADER %d\n", &ID[4]);
		printf("\n%d\n", ID[4]);
		fscanf(fp, "POSITION %f, %f, %f\nROTATION %f, %f, %f\nSCALE %f, %f, %f\n\n", &a[0], &a[1], &a[2], &a[3], &a[4], &a[5], &a[6], &a[7], &a[8]);
		printf("\n%f %f %f %f %f %f %f %f %f\n", a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]);
		printf("end\n");
		Object * obj;
		obj = ResourceManager::GetInstance()->Init(resource, ID, a, texture, cube);
		this->AddObject(obj);

	}
	fscanf(fp, "#CAMERA\nNEAR %f\nFAR %f\nFOV %f\nSPEED %f\n", &camera[0], &camera[1], &camera[2], &camera[3]);
	printf("%f %f %f %f", camera[0], camera[1], camera[2], camera[3]);
	myCamera = new Camera(camera);
	ResourceManager::GetInstance()->DestroyInstance();
}
