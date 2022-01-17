#include<iostream>
#include <bits/stdc++.h>

using namespace std;

const int EPS = 1;
const int ITN = 1000;


int func(int slow, int fast, int time)
{
    int fastCnt = time / fast;
    int slowCnt = (time - fast) / slow;

    return fastCnt + slowCnt;
}

int findTime(int copies, int xSpeed, int ySpeed)
{
    int fast = min(ySpeed, xSpeed);
    int slow = max(ySpeed, xSpeed);

    int mid;
    int right = copies * slow + 1;
    int left = fast - 1;


    while (right - left > EPS)
    {
        for (int i = 0; i < ITN; i++)
        {
            mid = (left + right) / 2;

            if (func(slow, fast, mid) < copies)
                left = mid;
            else
                right = mid;
        }
    }
    return right;
}

int main()
{
    int copies, xSpeed, ySpeed, temp;

    cin >> copies >> xSpeed >> ySpeed;

    cout << findTime(copies, xSpeed, ySpeed);

    return 0;
}
