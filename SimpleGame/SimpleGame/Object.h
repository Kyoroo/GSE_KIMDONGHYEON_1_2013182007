#pragma once

#define MAX_OBJECT_NUM 50
enum
{
	OBJECT_BUILDING,
	OBJECT_CHARACTER,
	OBJECT_BULLET,
	OBJECT_ARROW
};

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

struct Rect {
	float top;
	float bottom;
	float left;
	float right;
};

class Object
{
private:
	int m_id;
	Position m_pos;
	Color m_color;
	float m_size;
	Vector m_vector;
	Rect m_rect;
	int m_type;
	float m_life;
	float m_lifetime;
	float m_cooltime;
public:
	Position Get_position() const { return m_pos; }
	Color Get_color() const { return m_color; }
	float Get_size() const { return m_size; }
	Vector Get_vector() const { return m_vector; }
	Rect Get_rect() const { return m_rect; }
	int Get_type() const { return m_type; }
	float Get_life() const { return m_life; }
	float Get_lifetime() const { return m_lifetime; }
	float Get_cooltime() const { return m_cooltime; }
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
	void Set_rect(float x, float y)
	{
		m_rect.top = y + (m_size / 2);
		m_rect.bottom = y - (m_size / 2);
		m_rect.left = x - (m_size / 2);
		m_rect.right = x + (m_size / 2);
	}
	void Set_life(int life)
	{
		m_life = life;
	}
	void Set_lifetime(int lifetime)
	{
		m_lifetime = lifetime;
	}
	void Set_cooltime(float time)
	{
		m_cooltime = time;
	}
	Object(int type);
	~Object() {};
};