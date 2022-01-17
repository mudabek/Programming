#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100;
const int NO_EDGE = 100'000;
const int INF = 1'000'000;
int dist[MAX_N][MAX_N];
int next_[MAX_N][MAX_N];


void floyd(int &n)
{
    for (int k = 0; k < n; ++k)
    {
        for (int u = 0; u < n; ++u)
        {
            for (int v = 0; v < n; ++v)
            {
                if (dist[u][v] != INF && dist[u][k] != INF && dist[k][v] != INF
                    && dist[u][v] > dist[u][k] + dist[k][v])
                {
                    dist[u][v] = max(-INF, dist[u][k] + dist[k][v]);
                    if (dist[u][v] != -INF)
                        next_[u][v] = next_[u][k];
                }
            }
        }
    }
}


vector<int> getCycle(int n)
{
    vector<int> cycle;
    int cur;

    for (int t = 0; t < n; ++t)
    {
        if (dist[t][t] < 0)
        {
            cur = t;
            do {
                cycle.push_back(cur);
                cur = next_[cur][t];
            } while (cur != t);

            return cycle;
        }
    }

    return cycle;
}


int main()
{
    int n, temp;
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> temp;
            if (temp == NO_EDGE)
            {
                dist[i][j] = INF;
                next_[i][j] = -1;
            }
            else
            {
                dist[i][j] = temp;
                next_[i][j] = j;
            }
        }
    }

    floyd(n);

    vector<int> cycle = getCycle(n);

    if (cycle.size() == 0) {
        cout << "NO" << endl;
        return 0;
    }

    cout << "YES" << endl;
    cout << cycle.size() << endl;
    for (int i = 0; i < cycle.size(); ++i)
        cout << cycle[i] + 1 << " ";

    return 0;
}
