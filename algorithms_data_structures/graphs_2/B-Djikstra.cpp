#include <bits/stdc++.h>

using namespace std;

const int INF = INT_MAX;
typedef vector<pair<int, int>> graph;

struct comparator
{
    bool operator() (pair<int, int> i, pair<int, int> j)
    {
        return i.second > j.second;
    }
};

typedef priority_queue<pair<int, int>,
    vector<pair<int, int>>, comparator> minHeap;


void djikstra(graph* &g, int* dist, int &&start, int &gSize)
{
    bool* used = new bool[gSize];
    for (int i = 0; i < gSize; ++i)
        used[i] = false;

    dist[start] = 0;
    int next;

    minHeap q;
    q.push({start, 0});

    for(int i = 0; i < gSize; ++i)
    {
        if (q.size() == 0)
            break;

        while (used[q.top().first])
            q.pop();

        next = q.top().first;
        q.pop();

        used[next] = true;
        for (const auto& u : g[next])
        {
            if (!used[u.first])
            {
                if (dist[u.first] > dist[next] + u.second)
                {
                    dist[u.first] = dist[next] + u.second;
                    q.push({u.first, dist[u.first]});
                }
            }
        }
    }
}

int main()
{
    int edges, vertices, weight, v0, vf;

    cin >> vertices >> edges;

    graph* g = new graph[vertices];
    for (int i = 0; i < edges; ++i)
    {
        cin >> v0 >> vf >> weight;
        g[v0 - 1].push_back({vf - 1, weight});
        g[vf - 1].push_back({v0 - 1, weight});
    }

    int* dist = new int[vertices];
    for (int i = 0; i < vertices; ++i)
    {
        dist[i] = INF;
    }
    djikstra(g, dist, 0, vertices);

    for (int i = 0; i < vertices; ++i)
    {
        cout << dist[i] << " ";
    }

    return 0;
}
