#pragma once
#include <vector>
#include "Object.h"
#include "Camera.h"
#include "ResourceManager.h"
class SceneManager
{
private:
	vector<Object*> m_ListObject; 
protected:
	SceneManager() {}
	~SceneManager() {}
	SceneManager(const SceneManager &) {}
	SceneManager& operator =(const SceneManager &) {}
	static SceneManager * ms_pInstance;
public:
	Camera * myCamera;
	static void CreateInstance()
	{
		if (ms_pInstance == NULL)
			ms_pInstance = new SceneManager;
	}
	static SceneManager * GetInstance()
	{
		return ms_pInstance;
	}
	static void DestroyInstance()
	{
		if (ms_pInstance)
		{
			delete ms_pInstance;
			ms_pInstance = NULL;
		}
	}
	void Update(float frameTime);
	void Render();
	void AddObject(Object *object);
	void Init(char * scene, char * resource);
};

