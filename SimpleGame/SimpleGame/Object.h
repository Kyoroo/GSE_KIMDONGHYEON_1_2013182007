#pragma once
class Object
{
private:
	int m_id;
	float m_x, m_y, m_z;
public:
	Object(int i, float x, float y, float z) : m_id(i), m_x(x), m_y(y), m_z(z) {};
	~Object();
};

class Troop : public Object
{
public:
	Troop(int i, float x, float y, float z) : Object(i, x, y, z) {};
	~Troop();
};