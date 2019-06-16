#pragma once

#include <array>

namespace sbx
{
	class PerlinNoise
	{
	private:
		std::array<uint8_t, 256> m_permutations;

	public:
		PerlinNoise();
		PerlinNoise(uint32_t seed);

		void reseed(uint32_t seed);

		float noise(float x) const { return noise(x, 0, 0); }
		float noise(float x, float y) const { return noise(x, y, 0); }
		float noise(float x, float y, float z) const;

		float operator()(float x) const { return noise(x, 0, 0); }
		float operator()(float x, float y) const { return noise(x, y, 0); }
		float operator()(float x, float y, float z) const { return noise(x, y, z); }
	};
}
