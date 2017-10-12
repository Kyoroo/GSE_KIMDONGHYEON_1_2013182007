#include "stdafx.h"
#include "Renderer.h"
#include "Scene.h"


void Scene::Set_renderer(Renderer *pRenderer)
{
	renderer = pRenderer;
}

void Scene::Update()
{
	obj.Update();
}

void Scene::Render()
{
	renderer->DrawSolidRect(obj.Get_position().x, obj.Get_position().y, obj.Get_position().z,
		obj.Get_size(), obj.Get_color().r, obj.Get_color().g, obj.Get_color().b, obj.Get_color().a);
}

void Scene::MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		obj.Set_position((x-250), (250-y), 0);
}

Scene::Scene()
{
}


Scene::~Scene()
{
}
