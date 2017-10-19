#include "stdafx.h"
#include "Object.h"

Object::Object()
{
	std::default_random_engine dre(std::random_device{}());
	std::uniform_int_distribution<> ur(-100, 100);
	Set_color(1,1,1,1);
	Set_position(10, 10, 0);
	Set_size(5);
	Set_vector(ur(dre)*0.001+0.0001, ur(dre)*0.001+0.0001);
}

void Object::Update()
{

	m_pos.x += m_vector.x;
	m_pos.y += m_vector.y;
	if (m_pos.x > 250 || m_pos.x < -250)
		Set_vector(m_vector.x * -1, m_vector.y);
	if (m_pos.y > 250 || m_pos.y < -250)
		Set_vector(m_vector.x, m_vector.y * -1);
	
}

void Object::Render()
{
	
}