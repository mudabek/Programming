#include<iostream>
#include <bits/stdc++.h>

using namespace std;

const int ITN = 100000;


double func(int fieldV, int forestV, double border, double entPoint)
{
    double fieldTime = (sqrt((1 - border) * (1 - border) + entPoint * entPoint)) / fieldV;
    double forestTime = (sqrt((1 - entPoint) * (1 - entPoint) + border * border)) / forestV;
    return fieldTime + forestTime;
}

double findPoint(int fieldV, int forestV, double border)
{
    double m1, m2, time1, time2;
    double left = 0;
    double right = 1;

    for (int i = 0; i < ITN; i++)
    {
        m1 = left + (right - left) / 3;
        m2 = right - (right - left) / 3;
        time1 = func(fieldV, forestV, border, m1);
        time2 = func(fieldV, forestV, border, m2);

        if (time1 < time2)
            right = m2;
        else
            left = m1;
    }

    return right;
}

int main()
{
    int fieldV, forestV;
    double border;

    cin >> fieldV >> forestV >> border;
    cout << fixed << setprecision(4);
    cout << findPoint(fieldV, forestV, border);

    return 0;
}
