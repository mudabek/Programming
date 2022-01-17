#include <bits/stdc++.h>
using namespace std;

int CAP = 130000;
int PRIME = 191161;
int PRIME_ALPHA = 31;

class Map
{
public:

    list<pair<string, string>>* data;

    Map()
    {
        data = new list<pair<string, string>>[CAP];
    }


    unsigned int hashFunc(string s)
    {
        unsigned int sum = 0;
        int pwr = s.size();

        for(char& c: s)
        {
            sum += (int)c * pow(PRIME_ALPHA, pwr);
            pwr--;
        }

        sum = (sum % PRIME) % CAP;

        return sum;
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
    process();
    return 0;
}
