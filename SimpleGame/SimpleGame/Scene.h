#pragma once
#include "Object.h"

class Renderer;

class Scene
{
private:
	Object *obj[MAX_OBJECT_NUM];
	Renderer *renderer = nullptr;
	int Objnum = 0, Objcurrnum = 0;

public:
	void Set_renderer(Renderer *pRenderer);
	void Update();
	void Render();
	void MouseInput(int button, int state, int x, int y);
	bool Collision(const Object *a, const Object *b);
	Scene();
	~Scene();
};

