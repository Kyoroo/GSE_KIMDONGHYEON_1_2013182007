#pragma once
#include "Object.h"

class Renderer;

class Scene
{
private:
	Object obj;
	Renderer *renderer = nullptr;

public:
	void Set_renderer(Renderer *pRenderer);
	void Update();
	void Render();
	void MouseInput(int button, int state, int x, int y);
	Scene();
	~Scene();
};

