#include<iostream>
#include <bits/stdc++.h>

using namespace std;


int WHITE = 0;
int GRAY = 1;
int BLACK = 2;


bool dfsCycle(const int &v, int* &color, list<int>* &arr)
{
    color[v] = GRAY;

    for (auto const &i : arr[v])
    {
        if (color[i] == WHITE)
            dfsCycle(i, color, arr);
        if (color[i] == GRAY)
            return true;
    }
    color[v] = BLACK;
    return false;
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

    list<int>* arr = new list<int>[vertCnt];

    int temp1, temp2;
    for (int i = 0; i < edgeCnt; ++i)
    {
        cin >> temp1 >> temp2;
        temp1 = temp1 - 1;
        temp2 = temp2 - 1;
        arr[temp1].push_front(temp2);
    }

    //check for cycles
    int* color = new int[vertCnt];
    for (int i = 0; i < vertCnt; ++i)
        color[i] = WHITE;

    for (int i = 0; i < vertCnt; ++i)
    {
        if (color[i] == WHITE)
        {
            if (dfsCycle(i, color, arr))
            {
                cout << -1 << endl;
                return 0;
            }
        }
    }

    //sort by topological order
    bool* used = new bool[vertCnt];
    vector<int> ans;
    for (int i = 0; i < vertCnt; ++i)
        used[i] = false;

    for (int i = 0; i < vertCnt; ++i)
    {
        if (used[i] == false)
        {
            dfsSort(i, used, ans, arr);
        }
    }

    for (int i = 0; i < vertCnt; ++i)
    {
        cout << ans.back() + 1 << " ";
        ans.pop_back();
    }

    return 0;
}
