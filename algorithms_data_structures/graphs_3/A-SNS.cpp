#include <bits/stdc++.h>

using namespace std;

const int MAX_CAP = 300'001;
int p[MAX_CAP];
int ranks[MAX_CAP];
int maxs[MAX_CAP];
int mins[MAX_CAP];
int capacity[MAX_CAP];

void init(int n)
{
    for (int i = 1; i <= n; ++i)
    {
        p[i] = i;
        ranks[i] = 0;
        maxs[i] = i;
        mins[i] = i;
        capacity[i] = 1;
    }
}

int get(int x)
{
    if (p[x] != x)
    {
        p[x] = get(p[x]);
    }

    return p[x];
}

void join(int x, int y)
{
    x = get(x);
    y = get(y);

    if (x == y)
        return;

    if (ranks[x] > ranks[y])
        swap(x, y);

    if (ranks[x] == ranks[y])
        ranks[y] = ranks[y] + 1;

    p[x] = y;
    mins[x] = mins[y] =  min(mins[x], mins[y]);
    maxs[x] = maxs[y] = max(maxs[x], maxs[y]);
    capacity[y] = capacity[x] + capacity[y];
}

int main()
{
    int n;
    cin >> n;

    init(n);

    string oper;
    int x, y;
    while (cin >> oper)
    {
        if (oper == "union")
        {
            cin >> x >> y;
            join(x, y);
        }
        else
        {
            cin >> x;
            y = get(x);
            cout << mins[y] << " " << maxs[y] << " " << capacity[y] << endl;
        }
    }
    return 0;
}
