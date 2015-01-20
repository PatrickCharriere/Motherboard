
#pragma once
#ifndef h_shape
#define h_shape

#include "point.h"
#include "object.h"

class Shape
{
public:
	virtual ~Shape() {}	//Class shape is virtual
	Shape(point_t center, object_t type);

	point_t GetCenter();
	object_t GetObjectType();

	void SetCenter(point_t center);
	void SetObjectType(object_t type);

protected:
	point_t m_center;
	object_t m_object_type;
};

class Rectangle : public Shape
{
public:
	Rectangle(
		point_t m_center, 
		object_t type,
		int width,
		int height,
		float angle);

	int GetWidth();
	int	GetHeight();
	float GetAngle();

	void SetWidth(int width);
	void SetHeight(int height);
	void SetAngle(float angle);

private:
	int m_width;
	int m_height;
	float m_angle;
};

class Circle : public Shape
{
public:
	Circle(point_t center,
			object_t type,
			int radius);

	int GetRadius();
	void 	SetRadius(int radius);

private:
	int m_radius;
};


#endif
