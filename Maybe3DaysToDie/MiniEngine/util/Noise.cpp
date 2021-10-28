#include "MiniEngine.h"
#include "Noise.h"
#include <random>

CNoise::CNoise()
{
    for (int i = 0; i < 256; i++)
    {
        noiseTable[i] = i;
    }

    std::random_device seed;
    std::mt19937 random(seed());
    std::shuffle(std::begin(noiseTable), std::begin(noiseTable) + 256, random);

    for (int i = 0; i < 256; i++)
    {
        noiseTable[256 + i] = noiseTable[i];
    }
}

CNoise::CNoise(int seed)
{
    for (int i = 0; i < 256; i++)
    {
        noiseTable[i] = i;
    }

    std::mt19937 random(seed);
    std::shuffle(std::begin(noiseTable), std::begin(noiseTable) + 256, random);

    for (int i = 0; i < 256; i++)
    {
        noiseTable[256 + i] = noiseTable[i];
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

double CNoise::CalculationNoise(double _x, double _y, double _z)
{
    int X = static_cast<int>(std::floor(_x)) & 255;
    int Y = static_cast<int>(std::floor(_y)) & 255;
    int Z = static_cast<int>(std::floor(_z)) & 255;

    double x = _x - std::floor(_x);
    double y = _y - std::floor(_y);
    double z = _z - std::floor(_z);

    double u = Fade(x);
    double v = Fade(y);
    double w = Fade(z);

    int A = noiseTable[X] + Y;
    int AA = noiseTable[A] + Z;
    int AB = noiseTable[A + 1] + Z;
    int B = noiseTable[X + 1] + Y;
    int BA = noiseTable[B] + Z;
    int BB = noiseTable[B + 1] + Z;

    return Lerp(w, Lerp(v, Lerp(u, Grad(noiseTable[AA], x, y, z), Grad(noiseTable[BA], x - 1, y, z)), Lerp(u, Grad(noiseTable[AB], x, y - 1, z), Grad(noiseTable[BB], x - 1, y - 1, z))),
        Lerp(v, Lerp(u, Grad(noiseTable[AA + 1], x, y, z - 1), Grad(noiseTable[BA + 1], x - 1, y, z - 1)), Lerp(u, Grad(noiseTable[AB + 1], x, y - 1, z - 1), Grad(noiseTable[BB + 1], x - 1, y - 1, z - 1))));
}

double CNoise::Octave(int octaves, double x, double y, double z)
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
