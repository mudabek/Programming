#include<iostream>
#include <bits/stdc++.h>

using namespace std;

int DEFAULT_COLOR = INT_MAX;
int MAX_RIBS = 10000;

void dfsConnect(list<int>* &arr, int v, int* &color, int &cur)
{
    color[v] = cur;

    for(auto const& i : arr[v])
    {
        if(color[i] == DEFAULT_COLOR)
        {
            dfsConnect(arr, i, color, cur);
        }
    }
}

void dfsSort(const int &v, bool* &used, vector<int> &ans, list<int>* &arr)
{
    used[v] = true;

    for (auto const &i : arr[v])
    {
        if (!used[i])
        {
            dfsSort(i, used, ans, arr);
        }
    }
    ans.push_back(v);
}


int main()
{
    //input all the data
    int vertCnt, edgeCnt;
    cin >> vertCnt >> edgeCnt;

    list<int>* vertices = new list<int>[vertCnt];
    list<int>* verticesInv = new list<int>[vertCnt];

    int temp1, temp2;
    for (int i = 0; i < edgeCnt; ++i)
    {
        cin >> temp1 >> temp2;
        temp1 = temp1 - 1;
        temp2 = temp2 - 1;
        vertices[temp1].push_front(temp2);
        verticesInv[temp2].push_front(temp1);
    }

    //run topo sort of vertices
    bool* used = new bool[vertCnt];
    vector<int> sorted;
    for (int i = 0; i < vertCnt; ++i)
        used[i] = false;

    for (int i = 0; i < vertCnt; ++i)
    {
        if (used[i] == false)
        {
            dfsSort(i, used, sorted, vertices);
        }
    }

    //run connectivity on inverted vertices at topo sort order
    int colorCnt = 0;
    int* color = new int[vertCnt];
    reverse(sorted.begin(), sorted.end());

    for (int i = 0; i < vertCnt; ++i)
        color[i] = DEFAULT_COLOR;

    for (auto iter : sorted)
    {
        if (color[iter] == DEFAULT_COLOR)
        {
            colorCnt++;
            dfsConnect(verticesInv, iter, color, colorCnt);
        }
    }

    //count number of connections
    set<int>ribs[MAX_RIBS];
    for (int i = 0; i < vertCnt; ++i)
    {
        for (auto const& v : vertices[i])
            if (color[i] != color[v])
                ribs[color[i]].insert(color[v]);
    }

    int answer = 0;
    for(int i = 0; i < MAX_RIBS; i++)
        answer+=ribs[i].size();

    cout << answer;

    return 0;
}
