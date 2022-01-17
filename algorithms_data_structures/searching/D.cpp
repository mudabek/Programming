#include<iostream>
#include <bits/stdc++.h>

using namespace std;

const double EPS = 0.1;
const int ITN = 10000;

double func(double* arr, int arrLen, double maxLen)
{
    int cnt = 0;

    for (int i = 0; i < arrLen; i++)
    {
        cnt += (int)(arr[i] / maxLen);
    }
    return cnt;
}

double findMax(double* ropesArr, int ropesLen, int houseNum)
{
    double sum = 0;
    for (int i = 0; i < ropesLen; i++)
    {
        sum += ropesArr[i];
    }
    return sum / houseNum;
}

int findMaxLen(double* ropesArr, int ropesNum, int houseNum)
{
    double left = 0;
    double right = findMax(ropesArr, ropesNum, houseNum);

    if (right < 1)
        return 0;

    while (right - left > EPS)
    {
        for (int i = 0; i < ITN; i++)
        {
            double mid = (left + right) / 2;

            if (func(ropesArr, ropesNum, mid) < houseNum)
                right = mid;
            else
                left = mid;
        }
    }
    return (int)right;
}

int main()
{
    int ropesNum, housesNum, i;
    double temp;

    cin >> ropesNum >> housesNum;

    double ropesArr[ropesNum];

    for (i = 0; i < ropesNum; i++)
    {
        cin >> temp;
        ropesArr[i] = temp;
    }

    cout << findMaxLen(ropesArr, ropesNum, housesNum);

    return 0;
}
