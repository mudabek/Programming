#include<iostream>
#include <bits/stdc++.h>

using namespace std;

const double EPS = 0.0000001;
const double MAX = 10000000000;
const double MIN = 0.5;
const int ITN = 10000;

double func(double value)
{
    return value * value + sqrt(value);
}

double findVal(double value, double left, double right)
{
    while (right - left > EPS)
    {
        for (int i = 0; i < ITN; i++)
        {
            double mid = (left + right) / 2;

            if (func(mid) < value)
                left = mid;
            else
                right = mid;
        }
    }
    return right;
}

int main()
{
    double input;

    cin >> input;

    cout << fixed;
    cout << setprecision(6);
    cout << findVal(input, MIN, MAX);

    return 0;
}
