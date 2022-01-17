#include<iostream>
#include <bits/stdc++.h>

using namespace std;

const int MAX_VERT = 20000;

bool used[MAX_VERT];
int timer;
int tin[MAX_VERT], fup[MAX_VERT];

void dfs(int &v, vector<int>* &vertices, int parent, vector<int> &cutPoints)
{
    used[v] = true;
    timer = timer + 1;
    tin[v] = fup[v] = timer;
    int cnt = 0;

    for (auto to : vertices[v])
    {
        if (to == parent)
            continue;
        if (used[to])
            fup[v] = min(fup[v], tin[to]);
        else
        {
            dfs(to, vertices, v, cutPoints);
            fup[v] = min(fup[v], fup[to]);
            if (fup[to] >= tin[v] && parent != -1)
                cutPoints.push_back(v);
            cnt = cnt + 1;
        }
    }
    if (parent == -1 && cnt > 1)
        cutPoints.push_back(v);
}

int main()
{
    int vertCnt, edgeCnt;
    cin >> vertCnt >> edgeCnt;

    vector<int>* arr = new vector<int>[vertCnt];

    int temp1, temp2;
    for (int i = 0; i < edgeCnt; ++i)
    {
        cin >> temp1 >> temp2;
        temp1 = temp1 - 1;
        temp2 = temp2 - 1;
        arr[temp1].push_back(temp2);
        arr[temp2].push_back(temp1);
    }

    for (int i = 0; i < vertCnt; ++i)
    {
        used[i] = false;
    }

    vector<int> cutPoints;
    //timer = 0;
    for (int i = 0; i < vertCnt; ++i)
    {

        if (!used[i])
        {
            int beginning = -1;
            timer = 0;
            dfs(i, arr, beginning, cutPoints);
        }
    }

    sort(cutPoints.begin(), cutPoints.end());
    cout << cutPoints.size() << endl;

    for (int i = 0; i < cutPoints.size(); ++i)
    {
        cout << cutPoints[i] + 1 << " ";
    }
}
