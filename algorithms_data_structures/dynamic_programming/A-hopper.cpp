#include <bits/stdc++.h>
using namespace std;

pair<long long, vector<int>> maximCoins(int* prices, int colNum, int jump)
{
    pair<long long, int>* coinMove = new pair<long long, int>[colNum];
    vector<int> moves;
    int maxSoFar, bestInd;
    bool gotPos;

    coinMove[0] = pair<long  long, int>(0, 0);

    for (int i = 1; i < colNum; ++ i)
    {
        if (prices[i - 1] >= 0)
        {
            coinMove[i].first = coinMove[i - 1].first + prices[i];
            coinMove[i].second = i - 1;
        }
        else
        {
            bestInd = i - 1;
            maxSoFar = coinMove[i - 1].first;
            for (int j = i - 2; j >= i - jump; -- j)
            {
                if (prices[j] >= 0)
                {
                    maxSoFar = prices[j];
                    bestInd = j;
                    break;
                }
                if (coinMove[j].first > maxSoFar)
                {
                    maxSoFar = coinMove[j].first;
                    bestInd = j;
                }
            }
            coinMove[i].first = coinMove[bestInd].first + prices[i];
            coinMove[i].second = bestInd;
        }
    }

    int k = colNum - 1;
    moves.insert(moves.begin(), k);
    while (k != 0)
    {
        moves.insert(moves.begin(), coinMove[k].second);
        k = coinMove[k].second;
    }
    return pair<long long, vector<int>>(coinMove[colNum - 1].first, moves);
}

void process()
{
    int colNum, jump;

    scanf("%d", &colNum);
    scanf("%d", &jump);

    int* prices = new int[colNum];
    prices[0] = 0;
    prices[colNum - 1] = 0;

    for (int i = 1; i < colNum - 1; ++ i)
    {
        scanf("%d", &prices[i]);
    }

    pair<long long, vector<int>> result = maximCoins(prices, colNum, jump);

    printf("%d\n", result.first);
    printf("%d\n", result.second.size() - 1);

    long long temp;
    for (int j = 0; j < result.second.size(); ++ j)
    {
        temp = result.second[j] + 1;
        printf("%llu ", temp);
    }
    printf("\n");
}

int main()
{
    process();
    return 0;
}
