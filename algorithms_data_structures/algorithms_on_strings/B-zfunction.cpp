#include <bits/stdc++.h>

using namespace std;

int* zfunction(string s)
{
    int left = 0;
    int right = 0;
    int* z = new int[s.length()];

    for (int i = 1; i < s.length(); ++i)
    {
        z[i] = max(0, min(right - i, z[i - left]));
        while (i + z[i] < s.length() && s[z[i]] == s[i + z[i]])
            z[i] = z[i] + 1;
        if (i + z[i] > right)
        {
            left = i;
            right = i + z[i];
        }
    }
    return z;
}

int main()
{
    string word;
    cin >> word;

    int* z = zfunction(word);

    for (int i = 1; i < word.length(); ++i)
    {
        cout << z[i] << " ";
    }
    cout << endl;
    return 0;
}


