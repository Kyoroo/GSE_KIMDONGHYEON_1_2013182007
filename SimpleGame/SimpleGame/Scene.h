#pragma once
#include "Object.h"

class Renderer;

class Scene
{
private:
	Object *obj_ch[MAX_OBJECT_NUM];
	Object *obj_building;
	Renderer *renderer = nullptr;
	int Objnum = 0, Objcurrnum = 0;
	DWORD time;

public:
	void Set_renderer(Renderer *pRenderer);
	void Update(float time);
	void Render();
	void ObjUpdate(Object *a, float time);
	void MouseInput(int button, int state, int x, int y);
	void Collision();
	Scene();
	~Scene();
};

