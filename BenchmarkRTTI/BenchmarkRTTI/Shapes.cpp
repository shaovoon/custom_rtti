#include "Shapes.h"
#include <iostream>

namespace test
{
RTTI_DEFINITIONS(Shape)
RTTI_DEFINITIONS(Circle)
RTTI_DEFINITIONS(Triangle)
RTTI_DEFINITIONS(Polygon)
RTTI_DEFINITIONS(Rectangle)
RTTI_DEFINITIONS(Square)
RTTI_DEFINITIONS(Parallelogram)

void Circle::Draw()
{
	std::cout << "Circle:" << std::endl;
}

void Triangle::Draw()
{
	std::cout << "Triangle: Lengths: " << m_Lengths[0] << "," << m_Lengths[1] << "," << m_Lengths[2] << ", Angles: "
		<< m_Angles[0] << "," << m_Angles[1] << "," << m_Angles[2] << std::endl;
}

void Polygon::Draw()
{
	std::cout << "Polygon: Sides: " << m_Sides << ", Length:" << m_Length << std::endl;
}

void Rectangle::Draw()
{
	std::cout << "Rectangle: Width: " << m_Width << ", Height: " << m_Height << std::endl;
}

void Square::Draw()
{
	std::cout << "Square: Length: " << m_Width << std::endl;
}

void Parallelogram::Draw()
{
	std::cout << "Parallelogram: Width: " << m_Width << ", Height: " << m_Height << ", Angle: " << m_Angle << std::endl;
}

}