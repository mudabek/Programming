#include <bits/stdc++.h>
using namespace std;

const int MAX_CAP = 200'001;
int p[MAX_CAP];
int r[MAX_CAP];

int get(int x)
{
    if (p[x] != x)
    {
        p[x] = get(p[x]);
    }
    return p[x];
}

void join(int x, int y)
{
    x = get(x);
    y = get(y);
    if (x == y)
    {
        return;
    }

    if (r[x] > r[y])
    {
        swap(r[x], r[y]);
    }

    if (r[x] == r[y])
    {
        r[y] = r[y] + 1;
    }

    p[x] = y;
}

long long int getWeight(vector<pair<int, pair<int, int>>>& graph, int n, int m)
{
    long long int weight = 0;

    sort(graph.begin(), graph.end());

    for (int i = 0; i < m; i++)
    {
        if (get(graph[i].second.first) != get(graph[i].second.second))
        {
            weight += graph[i].first;
            join(graph[i].second.first, graph[i].second.second);
        }
    }

    return weight;
}

int main()
{
    int n, m, v1, v2, w;

    cin >> n >> m;

    vector<pair<int, pair<int, int>>> graph(m);

    for (int i = 0; i < n; i++)
    {
        p[i] = i;
        r[i] = 0;
    }

    for (int i = 0; i < m; i++)
    {
        cin >> v1 >> v2 >> w;
        graph[i] = {w, {v1 - 1, v2 - 1}};
    }

    cout << getWeight(graph, n, m) << endl;

    return 0;
}
