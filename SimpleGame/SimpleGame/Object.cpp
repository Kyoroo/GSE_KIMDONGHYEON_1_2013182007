#include "stdafx.h"
#include "Object.h"

Object::Object(int type)
{
	std::default_random_engine dre(std::random_device{}());
	std::uniform_int_distribution<> ur(-100, 100);
	if (type == OBJECT_BUILDING)
	{
		Set_color(1, 1, 0, 1);
		Set_position(0, 0, 0);
		Set_size(20);
		Set_vector(0, 0);
		Set_rect(Get_position().x, Get_position().y);
		Set_type(type);
		Set_life(1000);
		Set_lifetime(10000);
	}
	if (type == OBJECT_CHARACTER)
	{
		Set_color(1, 1, 1, 1);
		Set_position(200, 200, 0);
		Set_size(10);
		Set_vector(ur(dre)/100, ur(dre)/100);
		Set_rect(Get_position().x, Get_position().y);
		Set_type(type);
		Set_life(100);
		Set_lifetime(10000);
	}
}

void Object::Update(float time)
{
	float modified_time = time / 1000;
	m_pos.x = m_vector.x * modified_time * 10;
	m_pos.y = m_vector.y * modified_time * 10;
	if (m_pos.x > 250 || m_pos.x < -250)
		Set_vector(m_vector.x * -1, m_vector.y);
	if (m_pos.y > 250 || m_pos.y < -250)
		Set_vector(m_vector.x, m_vector.y * -1);
	if (m_lifetime > 0)
		m_lifetime -= modified_time;
}

void Object::Render()
{
	
}