#include "stdafx.h"
#include "Renderer.h"
#include "Scene.h"


void Scene::Set_renderer(Renderer *pRenderer)
{
	renderer = pRenderer;
	aliance_building = renderer->CreatePngTexture("./Source/Aliance.png");
	hord_building = renderer->CreatePngTexture("./Source/Hord.png");
	map_texture = renderer->CreatePngTexture("./Source/map.png");
	particle = renderer->CreatePngTexture("./Source/particle.png");
}

void Scene::Update(float time)
{
	std::default_random_engine dre(std::random_device{}());
	std::uniform_real_distribution<> x(-200, 200);
	std::uniform_real_distribution<> y(50, 350);
	float modified_time = time / 1000;
	time_team2 += modified_time;
	character_spawn_time += modified_time;
	if (time_team2 > 3)
	{
		int i = SpawnCharacter();
		obj_ch[i]->Set_position(x(dre), y(dre), 0);
		obj_ch[i]->Set_team(2);
		time_team2 = 0.0;
	}
	Collision();
	BulletCollision();
	for (int i = 0; i < MAX_OBJECT_NUM; ++i)
	{
		if (obj_ch[i] != NULL)
		{
			if (obj_ch[i]->Get_life() <= 0)
			{
				delete obj_ch[i];
				obj_ch[i] = NULL;
			}
			else
			{
				if (obj_ch[i]->Get_team() == 1)
				{
					obj_ch[i]->Set_color(0, 0, 1, 1);
				}
				else if (obj_ch[i]->Get_team() == 2)
				{
					obj_ch[i]->Set_color(1, 0, 0, 1);
				}
				ObjUpdate(obj_ch[i], time);
			}
		}
	}
	for (int i = 0; i < MAX_BULLET_NUM; ++i)
	{
		if (obj_bullet[i] != NULL)
		{
			if (obj_bullet[i]->Get_life() <= 0)
			{
				delete obj_bullet[i];
				obj_bullet[i] = NULL;
			}
			else
			{
				if (obj_bullet[i]->Get_team() == 1)
				{
					if (obj_bullet[i]->Get_type() == OBJECT_BULLET)
						obj_bullet[i]->Set_color(0, 0, 1, 1);
					else if (obj_bullet[i]->Get_type() == OBJECT_ARROW)
						obj_bullet[i]->Set_color(1, 1, 0, 1);
				}
				else if (obj_bullet[i]->Get_team() == 2)
				{
					if (obj_bullet[i]->Get_type() == OBJECT_BULLET)
						obj_bullet[i]->Set_color(1, 0, 0, 1);
					else if (obj_bullet[i]->Get_type() == OBJECT_ARROW)
						obj_bullet[i]->Set_color(0.5, 0.2, 0.7, 1);
				}
				ObjUpdate(obj_bullet[i], time);
			}
		}
	}
}

void Scene::Render()
{
	renderer->DrawTexturedRect(map->Get_position().x, map->Get_position().y, map->Get_position().z,
		map->Get_size(), map->Get_color().r, map->Get_color().g,map->Get_color().b, map->Get_color().a, map_texture, 1);
	for (int i = 0; i < MAX_OBJECT_NUM; ++i)
	{
		if (obj_ch[i] != NULL)
		{
			if (obj_ch[i]->Get_type() == OBJECT_BUILDING)
			{
				if (obj_ch[i]->Get_team() == 1)
				{
					renderer->DrawTexturedRect(obj_ch[i]->Get_position().x, obj_ch[i]->Get_position().y, obj_ch[i]->Get_position().z,
						obj_ch[i]->Get_size(), obj_ch[i]->Get_color().r, obj_ch[i]->Get_color().g, obj_ch[i]->Get_color().b, obj_ch[i]->Get_color().a, aliance_building, 0.1);
					renderer->DrawSolidRectGauge(obj_ch[i]->Get_position().x, obj_ch[i]->Get_position().y + (obj_ch[i]->Get_size() / 2), obj_ch[i]->Get_position().z + (obj_ch[i]->Get_size() / 2),
						obj_ch[i]->Get_size(), 5, obj_ch[i]->Get_color().r, obj_ch[i]->Get_color().g, obj_ch[i]->Get_color().b, obj_ch[i]->Get_color().a, (obj_ch[i]->Get_life() / 500), 0.1);
				}
				else if (obj_ch[i]->Get_team() == 2)
				{
					renderer->DrawTexturedRect(obj_ch[i]->Get_position().x, obj_ch[i]->Get_position().y, obj_ch[i]->Get_position().z,
						obj_ch[i]->Get_size(), obj_ch[i]->Get_color().r, obj_ch[i]->Get_color().g, obj_ch[i]->Get_color().b, obj_ch[i]->Get_color().a, hord_building, 0.1);
					renderer->DrawSolidRectGauge(obj_ch[i]->Get_position().x, obj_ch[i]->Get_position().y + (obj_ch[i]->Get_size() / 2), obj_ch[i]->Get_position().z + (obj_ch[i]->Get_size() / 2),
						obj_ch[i]->Get_size(), 5, obj_ch[i]->Get_color().r, obj_ch[i]->Get_color().g, obj_ch[i]->Get_color().b, obj_ch[i]->Get_color().a, (obj_ch[i]->Get_life() / 500), 0.1);
				}
			}
			else if(obj_ch[i]->Get_type() == OBJECT_CHARACTER)
			{
				if (obj_ch[i]->Get_team() == 2)
				{
					renderer->DrawSolidRect(obj_ch[i]->Get_position().x, obj_ch[i]->Get_position().y, obj_ch[i]->Get_position().z,
						obj_ch[i]->Get_size(), obj_ch[i]->Get_color().r, obj_ch[i]->Get_color().g, obj_ch[i]->Get_color().b, obj_ch[i]->Get_color().a, 0.2);
					renderer->DrawSolidRectGauge(obj_ch[i]->Get_position().x, obj_ch[i]->Get_position().y + obj_ch[i]->Get_size(), obj_ch[i]->Get_position().z + (obj_ch[i]->Get_size() / 2),
						obj_ch[i]->Get_size(), 5, obj_ch[i]->Get_color().r, obj_ch[i]->Get_color().g, obj_ch[i]->Get_color().b, obj_ch[i]->Get_color().a, (obj_ch[i]->Get_life() / 100), 0.1);
				}
				else if (obj_ch[i]->Get_team() == 1)
				{
					renderer->DrawSolidRect(obj_ch[i]->Get_position().x, obj_ch[i]->Get_position().y, obj_ch[i]->Get_position().z,
						obj_ch[i]->Get_size(), obj_ch[i]->Get_color().r, obj_ch[i]->Get_color().g, obj_ch[i]->Get_color().b, obj_ch[i]->Get_color().a, 0.2);
					renderer->DrawSolidRectGauge(obj_ch[i]->Get_position().x, obj_ch[i]->Get_position().y + obj_ch[i]->Get_size(), obj_ch[i]->Get_position().z + (obj_ch[i]->Get_size() / 2),
						obj_ch[i]->Get_size(), 5, obj_ch[i]->Get_color().r, obj_ch[i]->Get_color().g, obj_ch[i]->Get_color().b, obj_ch[i]->Get_color().a, (obj_ch[i]->Get_life() / 100), 0.1);
				}
			}
		}
	}
	for (int i = 0; i < MAX_BULLET_NUM; ++i)
	{
		if (obj_bullet[i] != NULL)
		{
			renderer->DrawSolidRect(obj_bullet[i]->Get_position().x, obj_bullet[i]->Get_position().y, obj_bullet[i]->Get_position().z,
				obj_bullet[i]->Get_size(), obj_bullet[i]->Get_color().r, obj_bullet[i]->Get_color().g, obj_bullet[i]->Get_color().b, obj_bullet[i]->Get_color().a, 0.3);
			if (obj_bullet[i]->Get_type() == OBJECT_BULLET)
			{
				renderer->DrawParticle(obj_bullet[i]->Get_position().x, obj_bullet[i]->Get_position().y, obj_bullet[i]->Get_position().z, 10,
					obj_bullet[i]->Get_color().r, obj_bullet[i]->Get_color().g, obj_bullet[i]->Get_color().b, obj_bullet[i]->Get_color().a, (obj_bullet[i]->Get_vector().x / 600) * -1, (obj_bullet[i]->Get_vector().y / 600) * -1, particle, obj_bullet[i]->Get_cooltime(), 0.3);
			}
		}
	}
}

void Scene::MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (character_spawn_time > 1)
		{
			if (((WINDOW_HEIGHT / 2) - y) < 0)
			{
				for (int i = 0; i < MAX_OBJECT_NUM; ++i)
				{
					if (obj_ch[i] == NULL)
					{
						obj_ch[i] = new Object(OBJECT_CHARACTER);
						obj_ch[i]->Set_position(x - (WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2) - y, 0);
						obj_ch[i]->Set_id(i);
						obj_ch[i]->Set_team(1);
						character_spawn_time = 0.0;
						break;
					}
				}
			}
		}
	}
}

int Scene::SpawnBullet()
{
	for (int i = 0; i < MAX_BULLET_NUM; ++i)
	{
		if (obj_bullet[i] == NULL)
		{
			obj_bullet[i] = new Object(OBJECT_BULLET);
			return i;
		}
	}
}

int Scene::SpawnArrow()
{
	for (int i = 0; i < MAX_BULLET_NUM; ++i)
	{
		if (obj_bullet[i] == NULL)
		{
			obj_bullet[i] = new Object(OBJECT_ARROW);
			return i;
		}
	}
}

int Scene::SpawnCharacter()
{
	std::default_random_engine dre(std::random_device{}());
	std::uniform_real_distribution<> x(-2, -0);
	for (int i = 0; i < MAX_OBJECT_NUM; ++i)
	{
		if (obj_ch[i] == NULL)
		{
			obj_ch[i] = new Object(OBJECT_CHARACTER);
			obj_ch[i]->Set_vector((x(dre)+1)*100, -100);
			return i;
		}
	}
}

void Scene::Collision()
{
	for (int i = 0; i < MAX_OBJECT_NUM; ++i)
	{
		for (int j = i + 1; j < MAX_OBJECT_NUM; ++j)
		{
			if (obj_ch[i] != NULL&&obj_ch[j] != NULL)
			{
				Rect a = obj_ch[i]->Get_rect();
				Rect b = obj_ch[j]->Get_rect();
				if (CollisionTest(a, b))
				{
					if (obj_ch[i]->Get_type() == OBJECT_BUILDING && obj_ch[j]->Get_type() == OBJECT_CHARACTER && (obj_ch[i]->Get_team() != obj_ch[j]->Get_team()))
					{
						obj_ch[i]->Set_life(obj_ch[i]->Get_life() - obj_ch[j]->Get_life());
						obj_ch[j]->Set_life(0);
					}
					else if (obj_ch[i]->Get_type() == OBJECT_CHARACTER && obj_ch[j]->Get_type() == OBJECT_BUILDING && (obj_ch[i]->Get_team() != obj_ch[j]->Get_team()))
					{
						obj_ch[j]->Set_life(obj_ch[j]->Get_life() - obj_ch[i]->Get_life());
						obj_ch[i]->Set_life(0);
					}
				}

			}
		}
		/*if (collision > 0)
		{
			if (obj_ch[i] != NULL && obj_ch[i]->Get_type() == OBJECT_BUILDING)
			{
				obj_ch[i]->Set_color(0, 1, 1, 1);
			}
		}
		else
		{
			if (obj_ch[i] != NULL && obj_ch[i]->Get_type() == OBJECT_BUILDING)
			{
				obj_ch[i]->Set_color(1, 1, 0, 1);
			}
		}*/
	}

}

void Scene::BulletCollision()
{
	for (int i = 0; i < MAX_OBJECT_NUM; ++i)
	{
		for (int j = 0; j < MAX_BULLET_NUM; ++j)
		{
			if (obj_ch[i] != NULL && obj_bullet[j] != NULL)
			{
				Rect a = obj_ch[i]->Get_rect();
				Rect b = obj_bullet[j]->Get_rect();
				if (CollisionTest(a, b))
				{
					if (obj_ch[i]->Get_type() == OBJECT_CHARACTER && obj_bullet[j]->Get_type() == OBJECT_BULLET && (obj_ch[i]->Get_team() != obj_bullet[j]->Get_team()))
					{
						obj_ch[i]->Set_life(obj_ch[i]->Get_life() - obj_bullet[j]->Get_life());
						obj_bullet[j]->Set_life(0);
					}
					if (obj_ch[i]->Get_type() == OBJECT_CHARACTER && obj_bullet[j]->Get_type() == OBJECT_ARROW && (obj_ch[i]->Get_team() != obj_bullet[j]->Get_team()))
					{
						obj_ch[i]->Set_life(obj_ch[i]->Get_life() - obj_bullet[j]->Get_life());
						obj_bullet[j]->Set_life(0);
					}
					if (obj_ch[i]->Get_type() == OBJECT_BUILDING && obj_bullet[j]->Get_type() == OBJECT_ARROW && (obj_ch[i]->Get_team() != obj_bullet[j]->Get_team()))
					{
						obj_ch[i]->Set_life(obj_ch[i]->Get_life() - obj_bullet[j]->Get_life());
						obj_bullet[j]->Set_life(0);
					}
					if (obj_ch[i]->Get_type() == OBJECT_BUILDING && obj_bullet[j]->Get_type() == OBJECT_ARROW && (obj_ch[i]->Get_team() != obj_bullet[j]->Get_team()))
					{
						obj_ch[i]->Set_life(obj_ch[i]->Get_life() - obj_bullet[j]->Get_life());
						obj_bullet[j]->Set_life(0);
					}
				}

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
	}
	for (int i = 0; i < MAX_BULLET_NUM; ++i)
	{
		obj_bullet[i] = NULL;
	}
	obj_ch[0] = new Object(OBJECT_BUILDING);
	obj_ch[0]->Set_id(0);
	obj_ch[0]->Set_position(-150, -300, 0);
	obj_ch[0]->Set_team(1);
	obj_ch[1] = new Object(OBJECT_BUILDING);
	obj_ch[1]->Set_id(1);
	obj_ch[1]->Set_position(0, -250, 0);
	obj_ch[1]->Set_team(1);
	obj_ch[2] = new Object(OBJECT_BUILDING);
	obj_ch[2]->Set_id(2);
	obj_ch[2]->Set_position(150, -300, 0);
	obj_ch[2]->Set_team(1);
	obj_ch[3] = new Object(OBJECT_BUILDING);
	obj_ch[3]->Set_id(3);
	obj_ch[3]->Set_position(-150, 300, 0);
	obj_ch[3]->Set_team(2);
	obj_ch[4] = new Object(OBJECT_BUILDING);
	obj_ch[4]->Set_id(4);
	obj_ch[4]->Set_position(0, 250, 0);
	obj_ch[4]->Set_team(2);
	obj_ch[5] = new Object(OBJECT_BUILDING);
	obj_ch[5]->Set_id(5);
	obj_ch[5]->Set_position(150, 300, 0);
	obj_ch[5]->Set_team(2);
	map = new Object(OBJECT_MAP);
	time_team2 = 0.0;
	character_spawn_time = 0.0;
}


Scene::~Scene()
{
	for (int i = 0; i < MAX_OBJECT_NUM; ++i)
	{
		if (obj_ch[i] != NULL)
		{
			delete obj_ch[i];
		}
	}
	for (int i = 0; i < MAX_BULLET_NUM; ++i)
	{
		if (obj_bullet[i] != NULL)
		{
			delete obj_bullet[i];
		}
	}
}

void Scene::ObjUpdate(Object *a, float time)
{
	std::default_random_engine dre(std::random_device{}());
	std::uniform_real_distribution<> x_vector(-2, -0);
	float modified_time = time / 1000;
	float x = a->Get_position().x + (a->Get_vector().x * modified_time);
	float y = a->Get_position().y + (a->Get_vector().y * modified_time);
	a->Set_position(x, y, 0);
	a->Set_rect(x, y);
	if (a->Get_lifetime() > 0) { a->Set_lifetime(a->Get_lifetime() - modified_time); }
	a->Set_cooltime(a->Get_cooltime() + time);
	if (a->Get_position().x >= (WINDOW_WIDTH / 2) || a->Get_position().x <= -(WINDOW_WIDTH / 2))
	{
		if (a->Get_type() == OBJECT_BULLET || a->Get_type() == OBJECT_ARROW)
		{
			a->Set_life(0);
		}
		a->Set_vector(a->Get_vector().x * -1, a->Get_vector().y);
		x = a->Get_position().x + (a->Get_vector().x * modified_time);
		y = a->Get_position().y + (a->Get_vector().y * modified_time);
		a->Set_position(x, y, 0);
		a->Set_rect(x, y);

	}
	if (a->Get_position().y >= (WINDOW_HEIGHT / 2) || a->Get_position().y <= -(WINDOW_HEIGHT / 2))
	{
		if (a->Get_type() == OBJECT_BULLET || a->Get_type() == OBJECT_ARROW)
		{
			a->Set_life(0);
		}
		a->Set_vector(a->Get_vector().x, a->Get_vector().y * -1);
		x = a->Get_position().x + (a->Get_vector().x * modified_time);
		y = a->Get_position().y + (a->Get_vector().y * modified_time);
		a->Set_position(x, y, 0);
		a->Set_rect(x, y);
	}
	if (a->Get_type() == OBJECT_BUILDING && a->Get_cooltime() > 5000)
	{
		int i = SpawnBullet();
		obj_bullet[i]->Set_position(a->Get_position().x, a->Get_position().y, 0);
		obj_bullet[i]->Set_rect(obj_bullet[i]->Get_position().x, obj_bullet[i]->Get_position().y);
		obj_bullet[i]->Set_team(a->Get_team());
		if (obj_bullet[i]->Get_team() == 1)
		{
			obj_bullet[i]->Set_vector((x_vector(dre) + 1) * 600, 600);
		}
		else
		{
			obj_bullet[i]->Set_vector((x_vector(dre) + 1) * 600, -600);
		}
		if (i >= 0)
		{
			obj_bullet[i]->Set_parent(a->Get_id());
		}
		a->Set_cooltime(0.0);

	}
	if (a->Get_type() == OBJECT_CHARACTER && a->Get_cooltime() > 3000)
	{
		int i = SpawnArrow();
		obj_bullet[i]->Set_position(a->Get_position().x, a->Get_position().y, 0);
		obj_bullet[i]->Set_rect(obj_bullet[i]->Get_position().x, obj_bullet[i]->Get_position().y);
		obj_bullet[i]->Set_team(a->Get_team());
		a->Set_cooltime(0.0);
		if (obj_bullet[i]->Get_team() == 1)
		{
			obj_bullet[i]->Set_vector((x_vector(dre) + 1) * 100, 100);
		}
		else
		{
			obj_bullet[i]->Set_vector((x_vector(dre) + 1) * 100, -100);
		}
		if (i >= 0)
		{
			obj_bullet[i]->Set_parent(a->Get_id());
		}

	}
}