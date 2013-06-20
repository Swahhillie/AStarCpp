#include "Random.hpp"
#include <chrono>

Random::Random()
{
	//ctor
}

Random::~Random()
{
	//dtor
}
int Random::inRange(int min, int max)
{
	seedGenerator();
	auto distribution = std::uniform_int_distribution<int>(min,max);
	return distribution(generator_);
}
float Random::inRange(float min, float max)
{
	seedGenerator();
	auto distribution = std::uniform_real_distribution<float>(min, max);
	return distribution(generator_);
}
void Random::seedGenerator()
{
	static bool seeded = false;
	if(!seeded)
	{
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		generator_ = std::default_random_engine(seed);
		seeded = true;
	}
}
float Random::value()
{
	return inRange(0.0f, 1.0f);
}
std::default_random_engine Random::generator_;
