#pragma once

#include <array>

namespace sbx
{
	class Noise
	{
	public:
		virtual ~Noise() = default;

		virtual void reseed(uint64_t seed) = 0;

		virtual double noise(double x) const = 0;
		virtual double noise(double x, double y) const = 0;
		virtual double noise(double x, double y, double z) const = 0;
		virtual double noise(double x, double y, double z, double w) const { return noise(x, y, z); }

		double operator()(double x) const { return noise(x, 0, 0); }
		double operator()(double x, double y) const { return noise(x, y, 0); }
		double operator()(double x, double y, double z) const { return noise(x, y, z); }
		double operator()(double x, double y, double z, double w) const { return noise(x, y, z, w); }
	};

	class PerlinNoise : public Noise
	{
	private:
		std::array<uint8_t, 256> m_perm;

	public:
		PerlinNoise();
		PerlinNoise(uint64_t seed);

		virtual void reseed(uint64_t seed) override;

		virtual double noise(double x) const override { return noise(x, 0, 0); }
		virtual double noise(double x, double y) const override { return noise(x, y, 0); }
		virtual double noise(double x, double y, double z) const override;
	};

	class SimplexNoise : public Noise
	{
	private:
		std::array<uint8_t, 256> m_perm;
		std::array<uint8_t, 256> m_permGradIndex3D;

	public:
		SimplexNoise();
		SimplexNoise(uint64_t seed);

		virtual void reseed(uint64_t seed) override;

		virtual double noise(double x) const override { return noise(x, 0); }
		virtual double noise(double x, double y) const override;
		virtual double noise(double x, double y, double z) const override;
		virtual double noise(double x, double y, double z, double w) const override;
	};
}
