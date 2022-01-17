#include <bits/stdc++.h>
using namespace std;

int CAP = 100000;
int PRIME = 191161;
int PRIME_ALPHA = 31;

class Map
{
public:

    vector<list<pair<string, string>>> data;

    Map()
    {
        vector<list<pair<string, string>>> data.resize(CAP, );
    }


    int hashFunc(string s)
    {
        int sum = 0;
        int cnt = 0;

        for(char& c: s)
        {
            sum += (int)c * pow(PRIME_ALPHA, cnt);
            cnt++;
        }

        sum = (sum % PRIME) % CAP;

        return abs(sum);
    }

    void put(string key, string value)
    {
        int index = hashFunc(key);
        pair<string, string> pr = pair<string, string>(key, value);



        for (auto const& i : data[index])
        {
            if (i.first == key)
            {
                data[index].remove(i);
                break;
            }
        }

        data[index].push_back(pr);
    }


    void rmve(string key)
    {
        int index = hashFunc(key);

        for (auto const& i : data[index])
        {
            if (i.first == key)
            {
                data[index].remove(i);
                return;
            }
        }
    }

    string get(string key)
    {
        int index = hashFunc(key);

        for (auto const& i : data[index])
        {
            if (i.first == key)
            {
                return i.second;
            }
        }
        return "none";
    }

};

void process()
{
    Map mp = Map();
    string oper, key, val;


    while (cin >> oper >> key)
    {
        if (oper == "put")
        {
            cin >> val;
            mp.put(key, val);
        }
        else if (oper == "get")
        {
            cout << mp.get(key) << endl;
        }
        else
        {
            mp.rmve(key);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    process();
    return 0;
}
