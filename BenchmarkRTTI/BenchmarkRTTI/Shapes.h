#pragma once

#include "RTTI.h"
namespace test
{
class Shape : public Library::RTTI
{
	RTTI_DECLARATIONS(Shape, RTTI)
	
public:
	virtual ~Shape() {};
	virtual void Draw() = 0;
};

class Circle : public Shape
{
	RTTI_DECLARATIONS(Circle, Shape)
	
public:
	Circle(int radius) : m_Radius(radius) {}
	void Draw();
	int getRadius() const { return m_Radius; }
	void setRadius(int val) { m_Radius = val; }
private:
	int m_Radius;
};

class Triangle : public Shape
{
	RTTI_DECLARATIONS(Triangle, Shape)
	
public:
	Triangle(int length1, float angle1,
		int length2, float angle2,
		int length3, float angle3)
	{
		m_Lengths[0] = length1;
		m_Lengths[1] = length2;
		m_Lengths[2] = length3;
		m_Angles[0] = angle1;
		m_Angles[1] = angle2;
		m_Angles[2] = angle3;
	}
	void Draw();
	void getLengths(int& length1, int& length2, int& length3)
	{
		length1 = m_Lengths[0];
		length2 = m_Lengths[1];
		length3 = m_Lengths[2];
	}
	void setLengths(int length1, int length2, int length3)
	{
		m_Lengths[0] = length1;
		m_Lengths[1] = length2;
		m_Lengths[2] = length3;
	}
	void getAngles(float& angle1, float& angle2, float& angle3)
	{
		angle1 = m_Angles[0];
		angle2 = m_Angles[1];
		angle3 = m_Angles[2];
	}
	void setAngles(float angle1, float angle2, float angle3)
	{
		m_Angles[0] = angle1;
		m_Angles[1] = angle2;
		m_Angles[2] = angle3;
	}

private:
	int m_Lengths[3];
	float m_Angles[3];
};

class Polygon : public Shape
{
	RTTI_DECLARATIONS(Polygon, Shape)
	
public:
	Polygon(int sides, int length) : m_Sides(sides), m_Length(length) {}
	void Draw();
	int getSides() const { return m_Sides; }
	void setSides(int val) { m_Sides = val; }
	int getLength() const { return m_Length; }
	void setLength(int val) { m_Length = val; }
private:
	int m_Sides;
	int m_Length;
};

class Rectangle : public Shape
{
	RTTI_DECLARATIONS(Rectangle, Shape)

public:
	Rectangle(int width, int height) : m_Width(width), m_Height(height) {}
	void Draw();
	int getWidth() const { return m_Width; }
	void setWidth(int val) { m_Width = val; }
	int getHeight() const { return m_Height; }
	void setHeight(int val) { m_Height = val; }
protected:
	int m_Width;
	int m_Height;
};

class Square : public Rectangle
{
	RTTI_DECLARATIONS(Square, Rectangle)

public:
	Square(int length) : Rectangle(length, length) {}
	int getLength() const { return m_Width; }
	void setLength(int val) { m_Width = val; }
	void Draw();
};

class Parallelogram : public Rectangle
{
	RTTI_DECLARATIONS(Parallelogram, Rectangle)

public:
	Parallelogram(int width, int height, float angle) : Rectangle(width,height), m_Angle(angle) {}
	void Draw();
	float getAngle() const { return m_Angle; }
	void setAngle(float val) { m_Angle = val; }
private:
	float m_Angle;
};
}