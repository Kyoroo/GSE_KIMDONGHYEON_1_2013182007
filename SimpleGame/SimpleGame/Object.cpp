#include "stdafx.h"
#include "Object.h"

Object::Object()
{
	Set_color(0,0,0,1);
	Set_position(10, 10, 0);
	Set_size(20);
	Set_vector(0.05, 0.05);
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