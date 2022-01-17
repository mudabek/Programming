[Forwarded from ~Lily]
    #include <algorithm>
    #include <iostream>
    #include <unordered_map>
    #include <vector>

    using namespace std;

    void to_lowercase(string& str) {
      transform(str.begin(), str.end(), str.begin(),
                [](unsigned char c) { return tolower(c); });
    }

    int dfs(int v, vector<bool>& used, vector<vector<int>>& graph, int count) {
      used[v] = true;
      int tmp = 0;
      int tmp2;
      for (const auto& iter : graph[v]) {
        if (!used[iter]) {
          tmp2 = dfs(iter, used, graph, tmp) + 1;
          count = max(count, tmp2);
        }
      }
      used[v] = false;
      return count;
    }

    int main() {
      ios_base::sync_with_stdio(false);
      cin.tie(0);
      cout.tie(0);

      int n;
      cin >> n;
      vector<vector<int>> graph(200);
      vector<bool> used(200, false);

      string p1, p2, tmp;
      int p1_num, p2_num;
      unordered_map<string, int> name_num_map;
      name_num_map["polycarp"] = 0;
      int cur_num = 1;
      for (int i = 0; i < n; i++) {
        cin >> p1 >> tmp >> p2;
        to_lowercase(p1);
        to_lowercase(p2);
        if (name_num_map.find(p1) != name_num_map.end()) {
          p1_num = name_num_map[p1];
        } else {
          p1_num = cur_num;
          name_num_map[p1] = cur_num;
          cur_num++;
        }
        if (name_num_map.find(p2) != name_num_map.end()) {
          p2_num = name_num_map[p2];
        } else {
          p2_num = cur_num;
          name_num_map[p2] = cur_num;
          cur_num++;
        }
        graph[name_num_map[p2]].push_back(name_num_map[p1]);
      }

      int len = 0;
      cout << dfs(0, used, graph, len) + 1;
      return 0;
    }




    /*
    for(int i = 1; i <= gSize; ++i)
    {
        next = -1;
        for(const auto& v : g[i])
        {
            if (next == - 1 || (dist[v.first] < dist[next] && !used[v.first]))
                next = v.first;
        }
        if (dist[next] == INF)
            break;
        used[next] = true;
        for (const auto& u : g[next])
            dist[u.first] = min(dist[u.first], dist[next] + u.second);
    }
    */
