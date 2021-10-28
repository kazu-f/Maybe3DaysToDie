#pragma once

class CNoise
{
public:
    CNoise();
    CNoise(int seed);
    double Fade(double t);
    double Lerp(double t, double a, double b);
    double Grad(int hash, double x, double y, double z);
    double CalculationNoise(double x, double y = 0.0, double z = 0.0);
    double Octave(int octaves, double x, double y = 0.0, double z = 0.0);
private:
    int noiseTable[512];
};
