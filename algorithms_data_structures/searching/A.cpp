#include<iostream>
#include <bits/stdc++.h>

using namespace std;

bool isLoCloser(int* arr, int lo, int hi, int target)
{
    if(target - arr[lo] <= arr[hi] - target)
        return true;
    else
        return false;
}

int findNearestHelper(int* arr, int lo, int hi, int target)
{
    if (lo == hi - 1)
    {
        if (isLoCloser(arr, lo, hi, target))
            return arr[lo];
        else
            return arr[hi];
    }

    int mid = (lo + hi) / 2;

    if (target == arr[mid])
    {
        return arr[mid];
    }

    if (target < arr[mid])
    {
        return findNearestHelper(arr, lo, mid, target);
    }
    else
    {
        return findNearestHelper(arr, mid, hi, target);
    }
}

int findNearest(int* arr, int lo, int hi, int target)
{
    if (arr[lo] > target)
        return arr[lo];

    if (arr[hi] < target)
        return arr[hi];

    return findNearestHelper(arr, lo, hi, target);
}

int main()
{
    int arrL, searchL, i, temp;

    cin >> arrL >> searchL;

    int arr[arrL], searchArr[searchL];

    for (i = 0; i < arrL; i++)
    {
        cin >> temp;
        arr[i] = temp;
    }

    for (i = 0; i < searchL; i++)
    {
        cin >> temp;
        searchArr[i] = temp;
    }

    for (i = 0; i < searchL; i++)
    {
        cout << findNearest(arr, 0, arrL - 1, searchArr[i]) << endl;
    }

    return 0;
}
