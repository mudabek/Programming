#include<iostream>
#include <bits/stdc++.h>

using namespace std;

int MAX_REPOSTS = 201;

void strToLow(string &data)
{
    transform(data.begin(), data.end(), data.begin(),
              [](unsigned char c)
    {
        return tolower(c);
    });
}


int dfs(int& v, bool* &used, list<int>* &vertices, int &cnt)
{
    used[v] = true;
    int temp = 0;
    int temp2;

    for (auto i : vertices[v])
    {
        if (!used[i])
        {
            temp2 = dfs(i, used, vertices, temp) + 1;
            cnt = max(cnt, temp2);
        }
    }
    used[v] = false;
    return cnt;
}

int main()
{
    int vertCnt;
    cin >> vertCnt;

    list<int>* vertices = new list<int>[MAX_REPOSTS];
    bool* used = new bool[MAX_REPOSTS];
    for (int i = 0; i < MAX_REPOSTS; ++i)
        used[i] = false;

    string parent, child, trash;
    int parentInt, childInt;
    unordered_map<string, int> assocMap;
    assocMap["polycarp"] = 0;
    int cur = 1;

    for (int i = 0; i < vertCnt; ++i)
    {
        cin >> child >> trash >> parent;
        strToLow(child);
        strToLow(parent);
        if (assocMap.find(child) != assocMap.end())
        {
            childInt = assocMap[child];
        }
        else
        {
            childInt = cur;
            assocMap[child] = cur;
            cur++;
        }
        if (assocMap.find(parent) != assocMap.end())
        {
            parentInt = assocMap[parent];
        }
        else
        {
            parentInt = cur;
            assocMap[parent] = cur;
            cur++;
        }
        vertices[assocMap[parent]].push_back(assocMap[child]);
    }


    int initMax = 0;
    int v = 0;
    cout << dfs(v, used, vertices, initMax) + 1;

    return 0;
}
