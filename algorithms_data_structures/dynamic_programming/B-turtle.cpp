#include <bits/stdc++.h>
using namespace std;


void turtleMoves(int** prices, int n, int m)
{
    int** coinMoves = new int*[n + 1];
    string result = "";
    vector<pair<int, int>> moves;


    for (int i = 0; i < n + 1; i++)
    {
        coinMoves[i] = new int[m + 1];
    }

    for (int i = 0; i < n + 1; i++)
    {
        coinMoves[i][0] = INT_MIN;
    }

    for (int i = 0; i < m + 1; i++)
    {
        coinMoves[0][i] = INT_MIN;
    }

    coinMoves[1][1] = prices[0][0];

    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < m + 1; j++)
        {
            if (i > 1 || j > 1)
            {
                if (coinMoves[i - 1][j] > coinMoves[i][j - 1])
                {
                    coinMoves[i][j] = coinMoves[i - 1][j] + prices[i - 1][j - 1];
                }
                else
                {
                    coinMoves[i][j] = coinMoves[i][j - 1] + prices[i - 1][j - 1];
                }
            }
        }
    }


    cout << coinMoves[n][m] << endl;
    int i = n, j = m;
    while (i != 1 || j != 1)
    {
        moves.push_back({i, j});
        if (coinMoves[i][j - 1] < coinMoves[i - 1][j])
        {
            result += "D";
            i = i - 1;
        }
        else
        {
            result += "R";
            j = j - 1;
        }
    }

    int len = moves.size();
    for (int i = 0; i < len; i++)
    {
        cout << result[len - i - 1];
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    int** prices = new int*[n];

    for (int i = 0; i < n; i++)
    {
        prices[i] = new int[m];
    }

    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < m; c++)
        {
            cin >> prices[r][c];
        }
    }

    turtleMoves(prices, n, m);

    return 0;
}
