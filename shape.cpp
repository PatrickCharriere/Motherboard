
#include "shape.h"

// Shape

Shape::Shape(point_t center, object_t type)
{
	this->m_center = center;
	this->m_object_type = type;
}

point_t Shape::GetCenter()
{
	return this->m_center;
}

object_t Shape::GetObjectType()
{
	return this->m_object_type;
}

void Shape::SetCenter(point_t center)
{
	this->m_center = center;
}

void Shape::SetObjectType(object_t object)
{
	this->m_object_type = object;
}

// Rectangle

Rectangle::Rectangle(
		point_t center,
		object_t type,
		int width,
		int height,
		float angle) :
	Shape(center, type),
	m_width(width),
	m_height(height),
	m_angle(angle)
{
}


int Rectangle::GetWidth()
{
	return this->m_width;
}

int Rectangle::GetHeight()
{
	return this->m_height;
}

float 	Rectangle::GetAngle()
{
	return this->m_angle;
}


void Rectangle::SetWidth(int width)
{
	this->m_width = width;
}

void Rectangle::SetHeight(int height)
{
	this->m_height = height;
}

void Rectangle::SetAngle(float angle)
{
	this->m_angle = angle;
}

// Circle

Circle::Circle(point_t center,
		object_t type,
		int radius) :
	Shape(center, type),
	m_radius(radius)
{
}

int Circle::GetRadius()
{
	return this->m_radius;
}

void 	Circle::SetRadius(int radius)
{
	this->m_radius = radius;
}
