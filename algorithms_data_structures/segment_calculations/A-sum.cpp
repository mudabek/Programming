#include <bits/stdc++.h>
using namespace std;

int MODN = pow(2, 16);
int MODM = pow(2, 30);

long long RSQ(int l, int r, long long* sums)
{
    if (l == 0)
    {
        return sums[r];
    }

    return sums[r] - sums[l - 1];
}

long long querySum(int* data, int* queries, int dataSize, int querySize)
{
    long long result = 0;

    long long* sums = new long long[dataSize];
    sums[0] = data[0];
    for (int i = 1; i < dataSize; ++i)
    {
        sums[i] = sums[i - 1] + data[i];
    }

    int l, r;
    int j = 0;

    while (j < querySize)
    {
        l = min(queries[j], queries[j + 1]);
        r = max(queries[j], queries[j + 1]);
        result = result + RSQ(l, r, sums);
        j = j + 2;
    }

    return result;
}

int main()
{
    int n, x, y, a, m, z, t, b;

    cin >> n >> x >> y >> a >> m >> z >> t >> b;

    int* data = new int[n];
    data[0] = a;
    for (int i = 1; i < n; ++i)
    {
        data[i] = (((x * data[i - 1] + y) % MODN) + MODN) % MODN;
    }

    int* queryNum = new int[2 * m];
    queryNum[0] = b;
    for (int i = 1; i < 2 * m; ++i)
    {
        queryNum[i] = (((z * queryNum[i - 1] + t) % MODM) + MODM) % MODM;
    }

    int* queries = new int[2 * m];
    for (int i = 0; i < 2 * m; ++i)
    {
        queries[i] = queryNum[i] % n;
    }

    if (m != 0)
        cout << querySum(data, queries, n, 2 * m) << endl;
    else
        cout << 0 << endl;

    return 0;
}
