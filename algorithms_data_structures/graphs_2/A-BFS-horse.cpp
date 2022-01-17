#include <bits/stdc++.h>

using namespace std;

const int MAXN = 21;
bool used[MAXN][MAXN];
typedef pair<int, int> coord;
vector<coord> graph[MAXN][MAXN];
coord path[MAXN][MAXN];
vector<coord> DELTA_MOVES = {{1, 2}, {2, 1}, {-1, 2}, {-2, 1},
                        {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};



void bfs(coord& s, coord& goal, queue<coord>& q)
{
    q.push(s);
    while (!q.empty())
    {
        coord v = q.front();
        q.pop();
        for (const auto& u : graph[v.first][v.second])
        {
            if (!used[u.first][u.second])
            {
                used[u.first][u.second] = true;
                path[u.first][u.second] = v;
                if (used[goal.first][goal.second])
                    return;
                q.push(u);
            }
        }
    }
}


int main()
{
    int boardSize, x0, y0, xf, yf, xtemp, ytemp;

    cin >> boardSize >> x0 >> y0 >> xf >> yf;

    coord start = {x0, y0};
    coord finish = {xf, yf};
    coord tempMove;

    for (int i = 0; i < boardSize; ++i)
    {
        for(int j = 0; j < boardSize; ++j)
        {
            used[i + 1][j + 1] = false;
            vector<coord> possibMoves;
            for (const auto& iter : DELTA_MOVES)
            {
                xtemp = i + 1 + iter.first;
                ytemp = j + 1 + iter.second;
                if (xtemp > 0 && xtemp <= boardSize &&
                    ytemp > 0 && ytemp <= boardSize)
                    {
                        tempMove = {xtemp, ytemp};
                        possibMoves.push_back(tempMove);
                    }
                graph[i + 1][j + 1] = possibMoves;
            }
        }
    }

    queue<coord> q;
    bfs(start, finish, q);

    stack<coord> result;
    tempMove = finish;
    while (tempMove != start)
    {
        result.push(tempMove);
        tempMove = path[tempMove.first][tempMove.second];
    }
    result.push(tempMove);

    cout << result.size() << endl;

    while (!result.empty())
    {
        cout << result.top().first << " " << result.top().second << endl;
        result.pop();
    }

    return 0;
}
