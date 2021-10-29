#pragma once

class CNoise
{
public:
    CNoise();
    CNoise(int seed);
    double Fade(double t);
    double Lerp(double t, double a, double b);
    double Grad(int hash, double x, double y, double z);
    double CalculationNoise(double _x, double _y = 0.0, double _z = 0.0);
    double Octave(int octaves, double x, double y = 0.0, double z = 0.0);
    //ノイズの範囲を指定する。
    void SetLimit(double minLimit, double maxLimit)
    {

    }
private:
    int noiseTable[512];
    double m_min = 0.0;
    double m_max = 1.0;
};
