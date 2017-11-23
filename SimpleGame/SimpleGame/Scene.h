#pragma once
#include "Object.h"

class Renderer;

class Scene
{
private:
	Object *obj_ch[MAX_OBJECT_NUM];
	Object *obj_bullet[MAX_BULLET_NUM];
	Renderer *renderer = nullptr;
	DWORD time;

public:
	void Set_renderer(Renderer *pRenderer);
	void Update(float time);
	void Render();
	void ObjUpdate(Object *a, float time);
	void MouseInput(int button, int state, int x, int y);
	void Collision();
	void BulletCollision();
	bool CollisionTest(Rect a, Rect b);
	int SpawnBullet();
	int SpawnArrow();
	Scene();
	~Scene();
};

