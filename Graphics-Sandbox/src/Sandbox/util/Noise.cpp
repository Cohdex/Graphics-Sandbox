#include "pch.h"
#include "Sandbox/util/Noise.h"

#include <random>
#include <chrono>
#include <algorithm>

#define p(x) m_permutations[(x) % 256]

namespace sbx
{
	static inline float fade(float t)
	{
		// 6t^5 - 15t^4 + 10t^3
		return t * t * t * (t * (t * 6 - 15) + 10);
	}

	static inline float grad(int hash, float x, float y, float z)
	{
		switch (hash & 0xF)
		{
		case 0x0: return  x + y;
		case 0x1: return -x + y;
		case 0x2: return  x - y;
		case 0x3: return -x - y;
		case 0x4: return  x + z;
		case 0x5: return -x + z;
		case 0x6: return  x - z;
		case 0x7: return -x - z;
		case 0x8: return  y + z;
		case 0x9: return -y + z;
		case 0xA: return  y - z;
		case 0xB: return -y - z;
		case 0xC: return  y + x;
		case 0xD: return -y + z;
		case 0xE: return  y - x;
		case 0xF: return -y - z;
		default: return 0; // never happens
		}
	}

	static inline float lerp(float a, float b, float t)
	{
		return a + t * (b - a);
	}

	PerlinNoise::PerlinNoise()
	{
		reseed(static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count()));
	}

	PerlinNoise::PerlinNoise(uint32_t seed)
	{
		reseed(seed);
	}

	void PerlinNoise::reseed(uint32_t seed)
	{
		for (int i = 0; i < 256; i++)
			m_permutations[i] = i;
		std::shuffle(m_permutations.begin(), m_permutations.end(), std::default_random_engine(seed));
	}

	float PerlinNoise::noise(float x, float y, float z) const
	{
		int xi = (int)x & 255;
		int yi = (int)y & 255;
		int zi = (int)z & 255;

		float xf = x - (int)x;
		float yf = y - (int)y;
		float zf = z - (int)z;

		float u = fade(xf);
		float v = fade(yf);
		float w = fade(zf);

		int aaa, aba, aab, abb, baa, bba, bab, bbb;
		aaa = p(p(p(xi) + yi) + zi);
		aba = p(p(p(xi) + yi + 1) + zi);
		aab = p(p(p(xi) + yi) + zi + 1);
		abb = p(p(p(xi) + yi + 1) + zi + 1);
		baa = p(p(p(xi + 1) + yi) + zi);
		bba = p(p(p(xi + 1) + yi + 1) + zi);
		bab = p(p(p(xi + 1) + yi) + zi + 1);
		bbb = p(p(p(xi + 1) + yi + 1) + zi + 1);

		float x1, x2, y1, y2;
		x1 = lerp(
			grad(aaa, xf, yf, zf),
			grad(baa, xf - 1, yf, zf),
			u);
		x2 = lerp(
			grad(aba, xf, yf - 1, zf),
			grad(bba, xf - 1, yf - 1, zf),
			u);
		y1 = lerp(x1, x2, v);

		x1 = lerp(
			grad(aab, xf, yf, zf - 1),
			grad(bab, xf - 1, yf, zf - 1),
			u);
		x2 = lerp(
			grad(abb, xf, yf - 1, zf - 1),
			grad(bbb, xf - 1, yf - 1, zf - 1),
			u);
		y2 = lerp(x1, x2, v);

		return (lerp(y1, y2, w) + 1) / 2;
	}
}
