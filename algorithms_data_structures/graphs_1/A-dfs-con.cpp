#include <iostream>
#include <list>

using namespace std;

int DEFAULT_COLOR = INT_MAX;

void dfs(list<int>* &arr, int v, int* &color, int &cur)
{
    color[v] = cur;

    for(auto const& i : arr[v])
    {
        if(color[i] == DEFAULT_COLOR)
        {
            dfs(arr, i, color, cur);
        }
    }
}

int main()
{
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
        arr[temp2].push_front(temp1);
    }

    int cnt = 0;
    int* color = new int[vertCnt];

    for (int i = 0; i < vertCnt; ++i)
        color[i] = DEFAULT_COLOR;

    for (int i = 0; i < vertCnt; ++i)
    {
        if (color[i] == DEFAULT_COLOR)
        {
            cnt++;
            dfs(arr, i, color, cnt);
        }
    }

    cout << cnt << endl;
    for (int i = 0; i < vertCnt; ++i)
        cout << color[i] << " ";

    return 0;
}
