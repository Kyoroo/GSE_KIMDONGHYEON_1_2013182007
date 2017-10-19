#include "stdafx.h"
#include "Renderer.h"
#include "Scene.h"


void Scene::Set_renderer(Renderer *pRenderer)
{
	renderer = pRenderer;
}

void Scene::Update()
{
	for (int i = 0; i < Objnum; ++i)
	{
		obj[i]->Update();
	}
}

void Scene::Render()
{
	for (int i = 0; i < Objnum; ++i)
	{
		renderer->DrawSolidRect(obj[i]->Get_position().x, obj[i]->Get_position().y, obj[i]->Get_position().z,
			obj[i]->Get_size(), obj[i]->Get_color().r, obj[i]->Get_color().g, obj[i]->Get_color().b, obj[i]->Get_color().a);
	}
}

void Scene::MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (Objcurrnum >= MAX_OBJECT_NUM - 1)
		{
			Objcurrnum = 0;
			delete(obj[Objcurrnum]);
		}
		obj[Objcurrnum] = new Object;
		obj[Objcurrnum]->Set_position((x - 250), (250 - y), 0);
		Objnum++;
		Objcurrnum++;
		if (Objnum >= MAX_OBJECT_NUM - 1)
		{
			Objnum = MAX_OBJECT_NUM - 1;
		}
	}
}

bool Scene::Collision(const Object *a, const Object *b)
{
	return false;
}

Scene::Scene()
{
}


Scene::~Scene()
{
}
