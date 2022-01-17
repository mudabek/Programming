#include <bits/stdc++.h>

using namespace std;

const int INF = INT_MAX;

struct Edge
{
    int s;
    int t;
    int c;
    int f;
    size_t index;
};

int pushFlow(int v, int t, int curFlow, vector<vector<Edge>>& g, bool* &used)
{
    used[v] = true;
    if (v == t)
    {
        return curFlow;
    }
    for (auto& e : g[v])
    {
        int u = e.t;
        if (!used[u] && e.f < e.c)
        {
            int nextFlow = min(curFlow, e.c - e.f);
            int delta = pushFlow(u, t, nextFlow, g, used);
            if (delta > 0)
            {
                g[u][e.index].f -= delta;
                e.f += delta;
                return delta;
            }
        }
    }
    return 0;
}

int fordFulk(vector<vector<Edge>>& g, int n)
{
    int result = 0;
    while (true)
    {
        bool* used = new bool[n];
        for (int i = 0; i < n; ++i)
            used[i] = false;

        int delta = pushFlow(0, n - 1, INF, g, used);
        if (delta > 0)
        {
            result = result + delta;
        }
        else
        {
            break;
        }
    }
    return result;
}

void addEdge(int s, int t, int c, vector<vector<Edge>>& g)
{
    g[s].push_back({s, t, c, 0, g[t].size()});
    g[t].push_back({t, s, 0, 0, g[s].size() - 1});
}

void dfs(const vector<vector<Edge>>& g, int s, bool* &used, const int maxFlow)
{
    used[s] = true;
    for (auto& e : g[s])
    {
        int t = e.t;
        if ((e.f != e.c) && !used[t])
        {
            dfs(g, t, used, maxFlow);
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<Edge>> g(n);
    vector<pair<int, int>> edges;
    int s, t, c;
    for (int i = 0; i < m; i++)
    {
        cin >> s >> t >> c;
        addEdge(s - 1, t - 1, c, g);
        addEdge(t - 1, s - 1, c, g);
        edges.push_back({s - 1, t - 1});
    }

    int maxFlow = fordFulk(g, n);

    bool* used = new bool[n];
    for (int i = 0; i < n; ++i)
        used[i] = false;

    dfs(g, 0, used, maxFlow);

    vector<int> ans;
    for (int i = 0; i < edges.size(); i++)
    {
        int s = edges[i].first;
        int t = edges[i].second;
        if (used[s] ^ used[t])
        {
            ans.push_back(i + 1);
        }
    }

    cout << ans.size() << " " << maxFlow << "\n";
    for (const auto& i : ans)
    {
        cout << i << " ";
    }

    return 0;
}
