// BenchmarkRTTI.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <iostream>
#include "Shapes.h"
#include "timer.h"

//#define CHECK_PTR 1

using namespace test;

void initVector(std::vector<test::Shape*>& vec);
void destroyVector(std::vector<test::Shape*>& vec);
void testDynamicCast(const std::vector<test::Shape*>& vec);
void testAsCast(const std::vector<test::Shape*>& vec);
void checkCircle(test::Circle* p);
void checkTriangle(test::Triangle* p);
void checkPolygon(test::Polygon* p);
void checkRectangle(test::Rectangle* p);
void checkSquare(test::Square* p);
void checkParallelogram(test::Parallelogram* p);

#ifdef WIN32

#pragma optimize("", off)
template <class T>
void do_not_optimize_away(T&& datum) {
	datum = datum;
}
#pragma optimize("", on)

#else
static void do_not_optimize_away(void* p) { 
    asm volatile("" : : "g"(p) : "memory");
}
#endif

int main()
{
	std::vector<Shape*> vec;
	initVector(vec);

	const size_t LOOP = 1000000;
	timer stopwatch;
	stopwatch.start_timing("DynamicCast");
	for(size_t i=0; i<LOOP; ++i)
	{
		testDynamicCast(vec);
	}
	stopwatch.stop_timing();
	stopwatch.start_timing("AsCast");
	for(size_t i=0; i<LOOP; ++i)
	{
		testAsCast(vec);
	}
	stopwatch.stop_timing();
	destroyVector(vec);
	return 0;
}

void initVector(std::vector<test::Shape*>& vec)
{
	{
		test::Shape* s = new test::Circle(10);
		vec.push_back(s);
	}
	{
		test::Shape* s = new test::Triangle(
			20, 60.0f,
			20, 60.0f,
			20, 60.0f);
		vec.push_back(s);
	}
	{
		test::Shape* s = new test::Polygon(5, 30);
		vec.push_back(s);
	}
	{
		test::Shape* s = new test::Rectangle(40, 50);
		vec.push_back(s);
	}
	{
		test::Shape* s = new test::Square(60);
		vec.push_back(s);
	}
	{
		test::Shape* s = new test::Parallelogram(70, 80, 85.0f);
		vec.push_back(s);
	}
}

void destroyVector(std::vector<test::Shape*>& vec)
{
	for(size_t i=0; i<vec.size(); ++i)
	{
		if(vec[i]!=NULL)
		{
			delete vec[i];
			vec[i] = NULL;
		}
	}

	vec.clear();
}

void testDynamicCast(const std::vector<test::Shape*>& vec)
{
	for(size_t i=0; i<vec.size(); ++i)
	{
		test::Circle* p = dynamic_cast<test::Circle*>(vec[i]);
		do_not_optimize_away(p);
#ifdef CHECK_PTR
		checkCircle(p);
#endif
	}
	for(size_t i=0; i<vec.size(); ++i)
	{
		test::Triangle* p = dynamic_cast<test::Triangle*>(vec[i]);
		do_not_optimize_away(p);
#ifdef CHECK_PTR
		checkTriangle(p);
#endif
	}
	for(size_t i=0; i<vec.size(); ++i)
	{
		test::Polygon* p = dynamic_cast<test::Polygon*>(vec[i]);
		do_not_optimize_away(p);
#ifdef CHECK_PTR
		checkPolygon(p);
#endif
	}
	for(size_t i=0; i<vec.size(); ++i)
	{
		test::Rectangle* p = dynamic_cast<test::Rectangle*>(vec[i]);
		do_not_optimize_away(p);
#ifdef CHECK_PTR
		checkRectangle(p);
#endif
	}
	for(size_t i=0; i<vec.size(); ++i)
	{
		test::Square* p = dynamic_cast<test::Square*>(vec[i]);
		do_not_optimize_away(p);
#ifdef CHECK_PTR
		checkSquare(p);
#endif
	}
	for(size_t i=0; i<vec.size(); ++i)
	{
		test::Parallelogram* p = dynamic_cast<test::Parallelogram*>(vec[i]);
		do_not_optimize_away(p);
#ifdef CHECK_PTR
		checkParallelogram(p);
#endif
	}
}

void testAsCast(const std::vector<Shape*>& vec)
{
	for(size_t i=0; i<vec.size(); ++i)
	{
		test::Circle* p = vec[i]->As<test::Circle>();
		do_not_optimize_away(p);
#ifdef CHECK_PTR
		checkCircle(p);
#endif
	}
	for(size_t i=0; i<vec.size(); ++i)
	{
		test::Triangle* p = vec[i]->As<test::Triangle>();
		do_not_optimize_away(p);
#ifdef CHECK_PTR
		checkTriangle(p);
#endif
	}
	for(size_t i=0; i<vec.size(); ++i)
	{
		test::Polygon* p = vec[i]->As<test::Polygon>();
		do_not_optimize_away(p);
#ifdef CHECK_PTR
		checkPolygon(p);
#endif
	}
	for(size_t i=0; i<vec.size(); ++i)
	{
		test::Rectangle* p = vec[i]->As<test::Rectangle>();
		do_not_optimize_away(p);
#ifdef CHECK_PTR
		checkRectangle(p);
#endif
	}
	for(size_t i=0; i<vec.size(); ++i)
	{
		test::Square* p = vec[i]->As<test::Square>();
		do_not_optimize_away(p);
#ifdef CHECK_PTR
		checkSquare(p);
#endif
	}
	for(size_t i=0; i<vec.size(); ++i)
	{
		test::Parallelogram* p = vec[i]->As<test::Parallelogram>();
		do_not_optimize_away(p);
#ifdef CHECK_PTR
		checkParallelogram(p);
#endif
	}
}

void checkCircle(test::Circle* p)
{
	if(p)
	{
		if(p->getRadius()!=10)
		{
			std::cerr << "Circle radius is not 10: " << p->getRadius() << std::endl;
		}
	}
}

void checkTriangle(test::Triangle* p)
{
	if(p)
	{
		int length1=0; int length2=0; int length3=0;
		p->getLengths(length1, length2, length3);
		if(length1!=20||length2!=20||length3!=20)
		{
			std::cerr << "Triangle length is not 20: " << length1 << "," << length2 << "," << length3 << std::endl;
		}
		float angle1=0.0f; float angle2=0.0f; float angle3=0.0f;
		p->getAngles(angle1, angle2, angle3);
		if(angle1!=60.0f||angle2!=60.0f||angle3!=60.0f)
		{
			std::cerr << "Triangle angle is not 60.0f: " << angle1 << "," << angle2 << "," << angle3 << std::endl;
		}
	}
}

void checkPolygon(test::Polygon* p)
{
	if(p)
	{
		if(p->getSides()!=5)
		{
			std::cerr << "Polygon number of sides is not 5: " << p->getSides() << std::endl;
		}
		if(p->getLength()!=30)
		{
			std::cerr << "Polygon length is not 30: " << p->getLength() << std::endl;
		}
	}
}

void checkRectangle(test::Rectangle* p)
{
	if(p)
	{
		if(p->getWidth()!=40&&p->getWidth()!=60&&p->getWidth()!=70)
		{
			std::cerr << "Rectangle width is wrong: " << p->getWidth() << std::endl;
		}
		if(p->getHeight()!=50&&p->getHeight()!=60&&p->getHeight()!=80)
		{
			std::cerr << "Rectangle height is wrong: " << p->getHeight() << std::endl;
		}
	}
}

void checkSquare(test::Square* p)
{
	if(p)
	{
		if(p->getLength()!=60)
		{
			std::cerr << "Square length is not 60: " << p->getLength() << std::endl;
		}
	}
}

void checkParallelogram(test::Parallelogram* p)
{
	if(p)
	{
		if(p->getWidth()!=70)
		{
			std::cerr << "Parallelogram width is not 70: " << p->getWidth() << std::endl;
		}
		if(p->getHeight()!=80)
		{
			std::cerr << "Parallelogram height is not 80: " << p->getHeight() << std::endl;
		}
		if(p->getAngle()!=85.0f)
		{
			std::cerr << "Parallelogram angle is not 85.0f: " << p->getAngle() << std::endl;
		}
	}
}