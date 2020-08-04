#pragma once
#include <vector>
#include "Object.h"
class ResourceManager
{
protected:
	ResourceManager() {}
	~ResourceManager() {}
	ResourceManager(const ResourceManager &) {}
	ResourceManager& operator =(const ResourceManager &) {}
	static ResourceManager * ms_pInstance;
public:
	static void CreateInstance()
	{
		if (ms_pInstance == NULL)
			ms_pInstance = new ResourceManager;
	}
	static ResourceManager * GetInstance()
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
	Object * Init(char * file, int * input, float * a, int * texture, int * cube);
};

