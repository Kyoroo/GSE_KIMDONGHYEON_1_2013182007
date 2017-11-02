#include "stdafx.h"
#include "Renderer.h"
#include "Scene.h"


void Scene::Set_renderer(Renderer *pRenderer)
{
	renderer = pRenderer;
}

void Scene::Update(float time)
{
	for (int i = 0; i < Objnum; ++i)
	{
		obj_ch[i]->Update(time);
	}
}

void Scene::Render()
{
	for (int i = 0; i < Objnum; ++i)
	{
		renderer->DrawSolidRect(obj_ch[i]->Get_position().x, obj_ch[i]->Get_position().y, obj_ch[i]->Get_position().z,
			obj_ch[i]->Get_size(), obj_ch[i]->Get_color().r, obj_ch[i]->Get_color().g, obj_ch[i]->Get_color().b, obj_ch[i]->Get_color().a);
	}
	renderer->DrawSolidRect(obj_building->Get_position().x, obj_building->Get_position().y, obj_building->Get_position().z,
		obj_building->Get_size(), obj_building->Get_color().r, obj_building->Get_color().g, obj_building->Get_color().b, obj_building->Get_color().a);
}

void Scene::MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (Objcurrnum >= MAX_OBJECT_NUM)
		{
			Objcurrnum = 0;
			delete(obj_ch[Objcurrnum]);
		}
		obj_ch[Objcurrnum] = new Object(OBJECT_CHARACTER);
		obj_ch[Objcurrnum]->Set_position((x - 250), (250 - y), 0);
		Objnum++;
		Objcurrnum++;
		if (Objnum >= MAX_OBJECT_NUM)
		{
			Objnum = MAX_OBJECT_NUM;
		}
	}
}

bool Scene::Collision(const Object *a, const Object *b)
{
	float temp_x = abs(a->Get_position().x - b->Get_position().x);
	float temp_y = abs(a->Get_position().y - b->Get_position().y);
	if (temp_x*temp_x + temp_y*temp_y <= a->Get_size()*a->Get_size())
		return true;
	return false;
}

Scene::Scene()
{
	obj_building = new Object(OBJECT_BUILDING);
}


Scene::~Scene()
{
}
