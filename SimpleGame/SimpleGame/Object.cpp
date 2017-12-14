#include "stdafx.h"
#include "Object.h"

Object::Object(int type) : m_type(type)
{
	std::default_random_engine dre(std::random_device{}());
	std::uniform_real_distribution<> ur(-2, 0);
	if (type == OBJECT_BUILDING)
	{
		Set_color(1, 1, 0, 1);
		Set_position(0, 0, 0);
		Set_size(100);
		Set_vector(0, 0);
		Set_rect(Get_position().x, Get_position().y);
		Set_life(500);
		Set_lifetime(10000);
		Set_cooltime(0);
	}
	if (type == OBJECT_CHARACTER)
	{
		Set_color(1, 1, 1, 1);
		Set_position(-100, -100, 0);
		Set_size(30);
		Set_vector((ur(dre) + 0.99) * 300, (ur(dre) + 0.99) * 300);
		Set_rect(Get_position().x, Get_position().y);
		Set_life(100);
		Set_lifetime(10000);
		Set_cooltime(0);
	}
	if (type == OBJECT_BULLET)
	{
		Set_color(1, 0, 0, 1);
		Set_size(4);
		Set_vector((ur(dre) + 1) * 300, (ur(dre) + 1) * 300);
		Set_rect(Get_position().x, Get_position().y);
		Set_life(15);
		Set_lifetime(10000);
		Set_cooltime(0);
	}
	if (type == OBJECT_ARROW)
	{
		Set_color(0, 1, 0, 1);
		Set_size(4);
		Set_vector((ur(dre) + 1) * 100, (ur(dre) + 1) * 100);
		Set_rect(Get_position().x, Get_position().y);
		Set_life(10);
		Set_lifetime(10000);
		Set_cooltime(0);
	}
	if (type == OBJECT_MAP)
	{
		Set_color(1, 1, 1, 1);
		Set_position(0, 0, 0);
		Set_size(800);
		Set_vector(0, 0);
		Set_rect(Get_position().x, Get_position().y);
		Set_life(0);
		Set_lifetime(0);
		Set_cooltime(0);
	}
}