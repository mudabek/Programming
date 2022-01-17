#include <bits/stdc++.h>
using namespace std;

void highestSubseq (int* seq, int seqLen)
{
    pair<int, int>* dp = new pair<int, int>[seqLen];

    dp[0] = {1, 0};
    //fill out where index coming from and max subseq at that index
    for (int i = 1; i < seqLen; i++)
    {
        dp[i] = {1, -1};
        for (int j = 0; j < i; j++)
        {
            if((seq[j] < seq[i]) && (dp[j].first + 1 > dp[i].first))
            {
                dp[i].first = dp[j].first + 1;
                dp[i].second = j;
            }
        }
    }

    //get index of maximum subsequence's end
    int maxIndex = 0;
    int max = dp[0].first;
    for (int i = 0; i < seqLen; i++)
    {
        if (max < dp[i].first)
        {
            maxIndex = i;
            max = dp[i].first;
        }
    }

    //print results
    cout << max << endl;
    int i = maxIndex;
    vector<int> steps;
    while (dp[i].first != 1)
    {
        steps.insert(steps.begin(), seq[i]);
        i = dp[i].second;
    }
    steps.insert(steps.begin(), seq[i]);

    for (int step : steps)
        cout << step << " ";
    cout << endl;
}


int main()
{
    int seqLen;
    cin >> seqLen;
    int* seq = new int[seqLen];

    for(int i = 0; i < seqLen; i++)
    {
        cin >> seq[i];
    }

    highestSubseq(seq, seqLen);
    return 0;
}
