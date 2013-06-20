#ifndef RANDOM_H
#define RANDOM_H

#include <SFML/System.hpp>
#include <random>
class Random : public sf::NonCopyable
{
	public:
		static int inRange(int min, int max);
		static float inRange(float min, float max);
		static float value(); // returns a number between 0.0f and 1.0f;
	protected:
	private:
		Random();
		virtual ~Random();
		static std::default_random_engine generator_;
		static void seedGenerator(); //seeds the generator
};

#endif // RANDOM_H
