#pragma once
#include <random>
#include <chrono>

class Random
{
public:
	static int nextInt(int a, int b)
	{
		unsigned seed = static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count());
		std::default_random_engine eng(seed);
		return eng() % (b - a) + a;
	}

	static float nextFloat(int a, int b)
	{
		return (float)nextInt(a, b);
	}
};