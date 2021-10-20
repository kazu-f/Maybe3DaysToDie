#include "MiniEngine.h"
#include "Noise.h"
#include <random>

CNoise::CNoise()
{
    for (int i = 0; i < 256; i++)
    {
        p[i] = i;
    }

    std::random_device seed;
    std::mt19937 random(seed());
    std::shuffle(std::begin(p), std::begin(p) + 256, random);

    for (int i = 0; i < 256; i++)
    {
        p[256 + i] = p[i];
    }
}

double CNoise::Fade(double t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double CNoise::Lerp(double t, double a, double b)
{
    return a + t * (b - a);
}

double CNoise::Grad(int hash, double x, double y, double z)
{
    int h = hash & 15;
    double u = h < 8 ? x : y;
    double v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

double CNoise::CalculationNoise(double x, double y, double z)
{
    int X = static_cast<int>(std::floor(x)) & 255;
    int Y = static_cast<int>(std::floor(y)) & 255;
    int Z = static_cast<int>(std::floor(z)) & 255;

    x -= std::floor(x);
    y -= std::floor(y);
    z -= std::floor(z);

    double u = Fade(x);
    double v = Fade(y);
    double w = Fade(z);

    int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z;
    int B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

    return Lerp(w, Lerp(v, Lerp(u, Grad(p[AA], x, y, z), Grad(p[BA], x - 1, y, z)), Lerp(u, Grad(p[AB], x, y - 1, z), Grad(p[BB], x - 1, y - 1, z))),
        Lerp(v, Lerp(u, Grad(p[AA + 1], x, y, z - 1), Grad(p[BA + 1], x - 1, y, z - 1)), Lerp(u, Grad(p[AB + 1], x, y - 1, z - 1), Grad(p[BB + 1], x - 1, y - 1, z - 1))));
}

double CNoise::Octave(double x, double y, double z, int octaves)
{
    double result = 0.0;
    double amp = 1.0;

    for (int i = 0; i < octaves; i++)
    {
        result += CalculationNoise(x, y, z) * amp;
        x *= 2.0;
        y *= 2.0;
        z *= 2.0;
        amp *= 0.5;
    }

    result = result * 0.5 + 0.5;
    if (result < 0) result = 0;
    else if (result > 1) result = 1;

    return result;
}
