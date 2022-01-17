#include <bits/stdc++.h>

using namespace std;

int P = 31;
const int MODER = 1e9 + 9;

int getHash(int l, int r, long long* hashes, long long* powp)
{
    if (l == 0)
        return hashes[r];

    return (hashes[r] - (hashes[l - 1] * powp[r - l + 1])
            % MODER + MODER) % MODER;
}

void init(string s, long long* &hashes, long long* &powp, int len)
{
    hashes[0] = s[0];
    powp[0] = 1;

    for (int i = 1; i < len; ++i)
    {
        hashes[i] = (hashes[i - 1] * P + s[i]) % MODER;
        powp[i] = (powp[i - 1] * P) % MODER;
    }
}

int main()
{
    int l1, l2, r1, r2, h1, h2, queries;
    string word;

    cin >> word >> queries;
    int wordLen = word.length();
    long long* hashes = new long long[wordLen];
    long long* powp = new long long[wordLen];

    init(word, hashes, powp, wordLen);

    for (int i = 0; i < queries; ++i)
    {
        cin >> l1 >> r1 >> l2 >> r2;
        if (r1 - l1 == r2 - l2)
        {
            h1 = getHash(l1 - 1, r1 - 1, hashes, powp);
            h2 = getHash(l2 - 1, r2 - 1, hashes, powp);
            if (h1 == h2)
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }

    return 0;
}
