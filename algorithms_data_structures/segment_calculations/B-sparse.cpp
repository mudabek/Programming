#include <iostream>
#include <cmath>
using namespace std;


int** makeTable(int* data, int n)
{
    int tableLen = log2(n) + 1;
    int** table = new int*[n];

    for (int i = 0; i < n; ++i)
    {
        table[i] = new int[tableLen];
    }

    for (int i = 0; i < n; ++i)
    {
        table[i][0] = data[i];
    }

    for (int j = 1; (1 << j) <= n; ++j)
    {
        for (int i = 0; i + (1 << j) <= n; ++i)
        {
            table[i][j] = min(table[i][j - 1],
                              table[i + (1 << (j - 1))][j - 1]);
        }
    }

    return table;
}


int rqm(int u, int v, int**& table)
{
    int l = min(u, v);
    int r = max(u, v);

    int pwr = (int)log2(r - l + 1);

    return min(table[l][pwr], table[r - (1 << pwr) + 1][pwr]);
}


int getA(int a)
{
    return (23 * a + 21563) % 16714589;
}


int getU(int u, int r, int i, int n)
{
    return ((17 * u + 751 + r + 2 * i) % n) + 1;
}

int getV(int v, int r, int i, int n)
{
    return ((13 * v + 593 + r + 5 * i) % n) + 1;
}


int main()
{
    int n, m, a, u, v, r;

    cin >> n >> m >> a >> u >> v;

    int* data = new int[n];
    data[0] = a;
    for (int i = 1; i < n; ++i)
    {
        data[i] = getA(data[i - 1]);
    }

    int** table = makeTable(data, n);

    r = rqm(u - 1, v - 1, table);

    for (int i = 1; i <= m; ++i)
    {
        if (i == m)
        {
            cout << u << " " << v << " " <<  r << endl;
            return 0;
        }
        u = getU(u, r, i, n);
        v = getV(v, r, i, n);
        r = rqm(u - 1, v - 1, table);
    }
}
