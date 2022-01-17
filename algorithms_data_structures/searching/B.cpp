#include<iostream>
#include <bits/stdc++.h>

using namespace std;

int lowerBound(int* arr, int length, int target)
{
    int left = -1;
    int right = length;

    while (left < right -1)
    {
        int mid = (left + right) / 2;
        if (target <= arr[mid])
            right = mid;
        else
            left = mid;
    }
    return right;
}

int upperBound(int* arr, int length, int target)
{
    return lowerBound(arr, length, target + 1);
}

int quickCount(int* arr, int length, int lo, int hi)
{
    int upperLim, lowerLim;

    if (arr[length - 1] < lo)
        return 0;
    else if (arr[length - 1] <= hi)
        upperLim = length;
    else
        upperLim = upperBound(arr, length, hi);

    if (arr[0] > hi)
        return 0;
    else if (arr[0] >= lo)
        lowerLim = 0;
    else
        lowerLim = lowerBound(arr, length, lo);

    return  upperLim - lowerLim;
}

int main()
{
    int arrL, reqs, lo, hi, temp, i;

    cin >> arrL;
    int arr[arrL];
    for (i = 0; i < arrL; i++)
    {
        cin >> temp;
        arr[i] = temp;
    }

    sort(arr, arr + arrL);

    cin >> reqs;
    int arrLo[reqs];
    int arrHi[reqs];
    for (i = 0; i < reqs; i++)
    {
        cin >> temp;
        arrLo[i] = temp;
        cin >> temp;
        arrHi[i] = temp;
    }

    for (i = 0; i < reqs; i++)
    {
        cout << quickCount(arr, arrL, arrLo[i], arrHi[i]) << " ";
    }

    return 0;
}
