#include <bits/stdc++.h>
using namespace std;

int fen(int i)
{
    return i & (i + 1);
}


long long* fenTable(long long*& data, int n)
{
    long long* table = new long long[n];

    for (int i = 0; i < n; i++)
    {
        table[i] = 0;
        for (int j = fen(i); j <= i; j++)
        {
            table[i] += data[j];
        }
    }

    return table;
}


long long get(int i, long long*& fTable)
{
    long long res = 0;
    while (i >= 0)
    {
        res += fTable[i];
        i = fen(i) - 1;
    }
    return res;
}


long long rsq(int l, int r, long long*& fTable)
{
    if (l == 0)
        return get(r, fTable);
    return get(r, fTable) - get(l - 1, fTable);
}


void add(int i, int val, long long*& fTable, int n)
{
    int j = i;
    while (j < n)
    {
        fTable[j] += val;
        j = j | (j + 1);
    }
}


void fSet(int index, long long& val, long long*& fTable, long long*& data, int n)
{
    int d = val - data[index];
    data[index] = val;
    add(index, d, fTable, n);

}


int main()
{
    int n, l, r, index;
    long long val;
    string oper;

    cin >> n;
    long long* data = new long long[n];
    for (int i = 0; i < n; ++i)
    {
        cin >> data[i];
    }

    long long* fTable = fenTable(data, n);

    while (cin >> oper)
    {
        if (oper == "sum")
        {
            cin >> l >> r;
            cout << rsq(l - 1, r - 1, fTable) << endl;
        }
        else
        {
            cin >> index >> val;
            fSet(index - 1, val, fTable, data, n);
        }
    }

    return 0;
}
