#pragma once

struct Color {
	float r;
	float g;
	float b;
	float a;
};

struct Position {
	float x;
	float y;
	float z;
};

struct Vector {
	float x;
	float y;
};

class Object
{
private:
	int m_id;
	Position m_pos;
	Color m_color;
	float m_size;
	Vector m_vector;
public:
	Position Get_position() const { return m_pos; }
	Color Get_color() const { return m_color; }
	float Get_size() const { return m_size; }
	Vector Get_vector() const { return m_vector; }
	void Set_position(float x, float y, float z)
	{
		m_pos.x = x, m_pos.y = y, m_pos.z = z;
	}
	void Set_color(float r, float g, float b, float a)
	{
		m_color.r = r, m_color.g = g, m_color.b = b, m_color.a = a;
	}
	void Set_size(float size) { m_size = size; }
	void Set_vector(float x, float y)
	{
		m_vector.x = x, m_vector.y = y;
	}
	void Update();
	void Render();
	Object();
	~Object() {};
};

class Troop : public Object
{
public:
	Troop();
	~Troop();
};