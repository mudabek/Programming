#include <bits/stdc++.h>

using namespace std;

const double INF = INT_MAX;

int minKey(double* result, bool* used, int n)
{
    double minim = INT_MAX;
    int minIndex;

    for (int i = 0; i < n; ++i)
        if (used[i] == false && result[i] < minim)
        {
            minim = result[i];
            minIndex = i;
        }

    return minIndex;
}

double getDistance(pair<int, int> p1, pair<int, int> p2)
{
    return sqrt(pow(p2.first - p1.first, 2) + pow(p2.second - p1.second, 2));
}

double* prim(vector<pair<int, int>> &points, double* &result, int &n)
{
    bool used[n];

    for (int i = 0; i < n; ++i)
    {
        used[i] = false;
    }

    result[0] = 0;
    double tempDist;
    int cur;
    for (int i = 0; i < n - 1; ++i)
    {
        cur = minKey(result, used, n);
        used[cur] = true;

        for (int j = 0; j < n; ++j)
        {
            tempDist = getDistance(points[cur], points[j]);
            if (used[j] == false && tempDist < result[j])
                result[j] = tempDist;
        }
    }

    return result;
}

int main()
{
    int n, x, y;

    cin >> n;

    vector<pair<int, int>> points;
    double* result = new double[n];
    for (int i = 0; i < n; ++i)
    {
        cin >> x >> y;
        points.push_back({x, y});
        result[i] = INF;
    }

    prim(points, result, n);

    double ans = 0;
    for (int i = 0; i < n; ++i)
    {
        ans = ans + result[i];
    }

    cout << ans;

    return 0;
}
