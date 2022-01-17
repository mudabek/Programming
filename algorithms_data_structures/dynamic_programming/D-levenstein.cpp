#include <bits/stdc++.h>
using namespace std;

void levenstein(string source, string goal)
{
    int rows = source.length() + 1;
    int cols = goal.length() + 1;

    int** dp = new int*[rows];
    for (int i = 0; i < rows; i++)
    {
        dp[i] = new int[cols];
    }

    for (int i = 0; i < rows; i++)
    {
        dp[i][0] = i;
    }

    for (int i = 0; i < cols; i++)
    {
        dp[0][i] = i;
    }

    int del, ins, chg, temp;
    for (int r = 1; r < rows; r++)
    {
        for (int c = 1; c < cols; c++)
        {
            if(source[r - 1] == goal[c - 1])
                dp[r][c] = dp[r - 1][c - 1];
            else
            {
                del = dp[r - 1][c - 1] + 1;
                ins = dp[r- 1][c] + 1;
                chg = dp[r][c - 1] + 1;
                temp = min(del, ins);
                dp[r][c] = min(temp, chg);
            }
        }
    }

    cout << dp[rows - 1][cols - 1] << endl;
}


int main()
{
    string source, goal;
    cin >> source >> goal;
    levenstein(source, goal);
    return 0;
}
