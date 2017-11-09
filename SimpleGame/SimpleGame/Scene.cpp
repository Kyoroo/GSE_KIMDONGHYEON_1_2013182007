#include "stdafx.h"
#include "Renderer.h"
#include "Scene.h"


void Scene::Set_renderer(Renderer *pRenderer)
{
	renderer = pRenderer;
}

void Scene::Update(float time)
{
	Collision();
	for (int i = 0; i < Objnum; ++i)
	{
		ObjUpdate(obj_ch[i], time);
	}
	ObjUpdate(obj_building, time);
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
		++Objnum;
		++Objcurrnum;
		if (Objnum >= MAX_OBJECT_NUM)
		{
			Objnum = MAX_OBJECT_NUM;
		}
	}
}

void Scene::Collision()
{
	int collision;
	int build_coll = 0;
	for (int i = 0; i < Objnum; ++i)
	{
		collision = 0;
		float temp_x = abs(obj_ch[i]->Get_position().x - obj_building->Get_position().x);
		float temp_y = abs(obj_ch[i]->Get_position().y - obj_building->Get_position().y);
		if (temp_x*temp_x + temp_y*temp_y <= obj_building->Get_size()*obj_building->Get_size())
		{
			++collision;
			++build_coll;
		}
		if (collision > 0)
		{
			obj_ch[i]->Set_color(1, 0, 0, 1);
		}
		else
		{
			obj_ch[i]->Set_color(1, 1, 1, 1);
		}
	}
	if (build_coll > 0)
	{
		obj_building->Set_color(1, 1, 0, 0.4);
	}
	else
	{
		obj_building->Set_color(1, 1, 0, 1);
	}
}

Scene::Scene()
{
	obj_building = new Object(OBJECT_BUILDING);
}


Scene::~Scene()
{
}

void Scene::ObjUpdate(Object *a, float time)
{
	float modified_time = time / 1000;
	float x = a->Get_position().x + (a->Get_vector().x * modified_time);
	float y = a->Get_position().y + (a->Get_vector().y * modified_time);
	a->Set_position(x, y, 0);
	if (a->Get_position().x > 250 || a->Get_position().x < -250)
		a->Set_vector(a->Get_vector().x * -1, a->Get_vector().y);
	if (a->Get_position().y > 250 || a->Get_position().y < -250)
		a->Set_vector(a->Get_vector().x, a->Get_vector().y * -1);
	if (a->Get_lifetime() > 0)
		a->Set_lifetime(a->Get_lifetime() - modified_time);
	a->Set_cooltime(a->Get_cooltime() + time);
}