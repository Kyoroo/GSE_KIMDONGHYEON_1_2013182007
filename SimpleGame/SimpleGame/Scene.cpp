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
	for (int i = 0; i < MAX_OBJECT_NUM; ++i)
	{
		if (obj_ch[i] != NULL)
		{
			if (obj_ch[i]->Get_life() == 0)
			{
				delete obj_ch[i];
				obj_ch[i] = NULL;
			}
			else
			{
				ObjUpdate(obj_ch[i], time);
			}
		}
	}
}

void Scene::Render()
{
	for (int i = 0; i < MAX_OBJECT_NUM; ++i)
	{
		if (obj_ch[i] != NULL)
		{
			renderer->DrawSolidRect(obj_ch[i]->Get_position().x, obj_ch[i]->Get_position().y, obj_ch[i]->Get_position().z,
				obj_ch[i]->Get_size(), obj_ch[i]->Get_color().r, obj_ch[i]->Get_color().g, obj_ch[i]->Get_color().b, obj_ch[i]->Get_color().a);
		}
	}
}

void Scene::MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = 0; i < MAX_OBJECT_NUM; ++i)
		{
			if (obj_ch[i] == NULL)
			{
				obj_ch[i] = new Object(OBJECT_CHARACTER);
				obj_ch[i]->Set_position(x - (WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2) - y, 0);
				break;
			}
		}
	}
}

void Scene::Collision()
{
	int collision;
	for (int i = 0; i < MAX_OBJECT_NUM; ++i)
	{
		collision = 0;
		for (int j = i + 1; j < MAX_OBJECT_NUM; ++j)
		{
			if (obj_ch[i] != NULL&&obj_ch[j] != NULL)
			{
				Rect a = obj_ch[i]->Get_rect();
				Rect b = obj_ch[j]->Get_rect();
				if (CollisionTest(a, b))
				{
					if (obj_ch[i]->Get_type() == OBJECT_BUILDING && obj_ch[j]->Get_type() == OBJECT_CHARACTER)
					{
						obj_ch[i]->Set_life(obj_ch[i]->Get_life() - obj_ch[j]->Get_life());
						obj_ch[j]->Set_life(0);
						collision++;
					}
					else if (obj_ch[i]->Get_type() == OBJECT_CHARACTER && obj_ch[j]->Get_type() == OBJECT_BUILDING)
					{
						obj_ch[j]->Set_life(obj_ch[j]->Get_life() - obj_ch[i]->Get_life());
						obj_ch[i]->Set_life(0);
						collision++;
					}
				}

			}
		}
		if (collision > 0)
		{
			if (obj_ch[i] != NULL && obj_ch[i]->Get_type() == OBJECT_BUILDING)
			{
				obj_ch[i]->Set_color(0, 1, 1, 0.4);
			}
		}
		else
		{
			if (obj_ch[i] != NULL && obj_ch[i]->Get_type() == OBJECT_BUILDING)
			{
				obj_ch[i]->Set_color(1, 1, 0, 1);
			}
		}
	}

}

bool Scene::CollisionTest(Rect a, Rect b)
{
	if (a.left > b.right)
		return false;
	if (a.right < b.left)
		return false;

	if (a.top < b.bottom)
		return false;
	if (a.bottom > b.top)
		return false;

	return true;
}

Scene::Scene()
{
	for (int i = 0; i < MAX_OBJECT_NUM; ++i)
	{
		obj_ch[i] = NULL;
		obj_bullet[i] = NULL;
	}
	obj_ch[0] = new Object(OBJECT_BUILDING);
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
	a->Set_rect(x, y);
	if (a->Get_position().x >= (WINDOW_WIDTH/2) || a->Get_position().x <= -(WINDOW_WIDTH / 2))
		a->Set_vector(a->Get_vector().x * -1, a->Get_vector().y);
	if (a->Get_position().y >= (WINDOW_HEIGHT/2) || a->Get_position().y <= -(WINDOW_HEIGHT / 2))
		a->Set_vector(a->Get_vector().x, a->Get_vector().y * -1);
	if (a->Get_lifetime() > 0)
		a->Set_lifetime(a->Get_lifetime() - modified_time);
	a->Set_cooltime(a->Get_cooltime() + time);
}