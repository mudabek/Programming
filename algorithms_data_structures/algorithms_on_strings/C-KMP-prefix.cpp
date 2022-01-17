#include <bits/stdc++.h>

using namespace std;

int* pfunction(string s, int len)
{
    int k;
    int* p = new int[len];
    p[0] = 0;

    for (int i = 1; i < len; ++i)
    {
        k = p[i - 1];
        while (k > 0 && s[i] != s[k])
            k = p[k - 1];
        if (s[i] == s[k])
            k++;
        p[i] = k;
    }

    return p;
}

int main()
{
    string prefix, word;
    cin >> prefix >> word;
    string kmp = prefix + "#" + word;
    int pLen = prefix.length();
    int kmpLen = kmp.length();

    int* p = pfunction(kmp, kmpLen);

    vector<int> occurs;
    for (int i = pLen + 2; i < kmpLen; ++i)
    {
        if (p[i] == pLen)
            occurs.push_back(i - 2 * pLen + 1);
    }

    cout << occurs.size() << endl;

    for (int i = 0; i < occurs.size(); ++i)
    {
        cout << occurs[i] << " ";
    }

    return 0;
}
