#ifndef SFMATH_HPP_INCLUDED
#define SFMATH_HPP_INCLUDED

#include <math.h>


namespace sf
{
namespace vec
{
//should probably be in some math header
static constexpr float PI = 3.14159265f;
static constexpr float degToRad = PI / 180.0f;
static constexpr float radToDeg = 360 / (PI * 2);


static sf::Vector2f rotate(const sf::Vector2f & v, float degrees)
{
    float cosRadians = cos(degrees * degToRad);
    float sinRadians = sin(degrees * degToRad);

    return sf::Vector2f(
               v.x * cosRadians - v.y * sinRadians,
               v.x * sinRadians + v.y * cosRadians);
}
static float magnitude(const sf::Vector2f & v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}
static float sqrMagnitude(const sf::Vector2f & v)
{
    return (v.x * v.x + v.y * v.y);
}

static float magnitude(const sf::Vector3f & v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}
static float sqrMagnitude(const sf::Vector3f & v)
{
    return (v.x * v.x + v.y * v.y + v.z * v.z);
}
static float dot(const sf::Vector2f & a, const sf::Vector2f & b)
{
	return (a.x * b.x + a.y * b.y);
}
static float dot(const sf::Vector3f & a, const sf::Vector3f & b)
{
	return (a.x * b.x + a.y * b.y + a.x * b.y);
}
static sf::Vector2f normalize(const sf::Vector2f & v)
{
	return v / magnitude(v);
}
static sf::Vector3f normalize(const sf::Vector3f & v)
{
	return v / magnitude(v);
}
}
}

#include "UnitTest++.h"
#include <iostream>

TEST(rotateVector2)
{
	//test values
	const sf::Vector2f up(0.0f,1.0f);
	const sf::Vector2f down(0.0f, -1.0f);
	const sf::Vector2f right(1.0f, 0.0f);
	const sf::Vector2f left(-1.0f, 0.0f);

	//comp function
	auto approxCompare = [](const sf::Vector2f & a, const sf::Vector2f & b)
	{
		return std::fabs(a.x - b.x) < std::numeric_limits<float>::epsilon() &&
		 std::fabs(a.y - b.y) < std::numeric_limits<float>::epsilon();
	};

	//rotate by 0. should remain the same
	sf::Vector2f rotated0 = sf::vec::rotate(up, 0.f);

	CHECK(approxCompare(up, rotated0));

	//full circle should be the same
	sf::Vector2f rotated360 = sf::vec::rotate(up, 360.0f);
	CHECK(approxCompare(up, rotated360));

	//plain
	CHECK(approxCompare(left, sf::vec::rotate(up, 90.0f)));

	//rotate 180 twice
	CHECK(approxCompare(up, sf::vec::rotate(sf::vec::rotate(up, 180.0f), 180.f )));

	//flip
	CHECK(approxCompare(up, sf::vec::rotate(down, 180.0f)));



}

TEST(magnitudes)
{
	using namespace sf::vec;

	auto approxCompare = [](float a, float b)
	{

		bool result = std::fabs(a - b) < std::numeric_limits<float>::epsilon();
		CHECK (std::fabs(a - b) < std::numeric_limits<float>::epsilon());
		if(!result) std::cout << a << " != " << b << std::endl;
	};

	//0
	approxCompare(magnitude(sf::Vector3f(0,0,0)), 0.f);

	approxCompare(magnitude(sf::Vector3f(1.0f, 0, 0)) , 1.0f);
	approxCompare(magnitude(sf::Vector3f(1.0f, 1.0f, 0)) , sqrtf(2));
	approxCompare(magnitude(sf::Vector3f(1.0f, 1.0f, 1.0f)) , sqrtf(3));
	approxCompare(magnitude(sf::Vector3f(1.0f, -1.0f, 0)) , sqrtf(2));
	approxCompare(magnitude(sf::Vector3f(-1.0f, -2.0f, 0)) , sqrtf(5)); // 1 * 1 + 2 * 2


}
TEST(sqrMagnitudes)
{
	using namespace sf::vec;

	auto approxCompare = [](float a, float b)
	{

		bool result = std::fabs(a - b) < std::numeric_limits<float>::epsilon();
		CHECK (std::fabs(a - b) < std::numeric_limits<float>::epsilon());
		if(!result) std::cout << a << " != " << b << std::endl;
	};

	//0
	approxCompare(sqrMagnitude(sf::Vector3f(0,0,0)), 0.f);

	approxCompare(sqrMagnitude(sf::Vector3f(1.0f, 0, 0)) , 1.0f);
	approxCompare(sqrMagnitude(sf::Vector3f(1.0f, 1.0f, 0)) , 2);
	approxCompare(sqrMagnitude(sf::Vector3f(1.0f, 1.0f, 1.0f)) , 3);
	approxCompare(sqrMagnitude(sf::Vector3f(1.0f, -1.0f, 0)) , 2);
	approxCompare(sqrMagnitude(sf::Vector3f(-1.0f, -2.0f, 0)) , 5); // 1 * 1 + 2 * 2

}

TEST(normalizedVector)
{
	using namespace sf::vec;
	auto approxCompare = [](const sf::Vector3f & toNormalize, const sf::Vector3f & b)
	{
		// b is expected
		sf::Vector3f a = normalize(toNormalize);

		bool result = std::fabs(a.x - b.x) < std::numeric_limits<float>::epsilon() &&
		 std::fabs(a.y - b.y) < std::numeric_limits<float>::epsilon() &&
		 std::fabs(a.z - b.z) < std::numeric_limits<float>::epsilon()
		 ;
		 CHECK(result);
	};
	//testing normalize with normalize... not a very good practice
	approxCompare(sf::Vector3f(100, 0, 0) , normalize(sf::Vector3f(1,0,0)));
	approxCompare(sf::Vector3f(100, 100, 0) , normalize(sf::Vector3f(1,1,0)));
	approxCompare(sf::Vector3f(-100, 100, 0) , normalize(sf::Vector3f(-1,1,0)));
	approxCompare(sf::Vector3f(-200, 100, 0) ,normalize( sf::Vector3f(-2,1,0)));
	approxCompare(sf::Vector3f(100, -100, 0) ,normalize( sf::Vector3f(1,-1,0)));


}

std::ostream & operator << (std::ostream & out, const sf::Vector3f & toPrint)
{
	auto cur = out.precision(3);
	out << "(" << toPrint.x << "," << toPrint.y << "," << toPrint.z << ")";
	out.precision (cur);
	return out;
}
std::ostream & operator << (std::ostream & out, const sf::Vector2f & toPrint)
{
	auto cur = out.precision(3);

	out << "(" << toPrint.x << "," << toPrint.y << ")";
	out.precision (cur);
	return out;
}
TEST(dotProduct)
{
	using namespace sf::vec;
	auto i = 0;
	auto approxCompare = [&](float a, float b)
	{

		bool result = std::fabs(a - b) < std::numeric_limits<float>::epsilon();
		CHECK (std::fabs(a - b) < std::numeric_limits<float>::epsilon());
		if(!result) std::cout << "# " << i << ":\t" << a << " != " << b << std::endl;
		i++;
	};

	//normal
	approxCompare(dot(sf::Vector3f(0,1,0), sf::Vector3f(1,0,0)), 0 );
	approxCompare(dot(sf::Vector3f(0,2,0), sf::Vector3f(2,0,0)), 0 );

	//parallel
	approxCompare(dot(sf::Vector3f(0,1,0), sf::Vector3f(0,1,0)), 1 );
	approxCompare(dot(sf::Vector3f(0,100,0), sf::Vector3f(0,100,0)), 10000 );

	//anti parallel
	approxCompare(dot(sf::Vector3f(0,1,0), sf::Vector3f(0,-1,0)), -1);
	approxCompare(dot(sf::Vector3f(0,10,0), sf::Vector3f(0,-10,0)), -100);


}
#endif // SFMATH_HPP_INCLUDED
