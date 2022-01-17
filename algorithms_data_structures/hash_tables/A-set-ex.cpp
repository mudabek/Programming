#include <bits/stdc++.h>
using namespace std;

class Set
{
public:

};



void process()
{
    Set st = Set();
    string oper;
    int temp;

    while (cin >> oper >> temp)
    {
        if (oper == "insert")
        {
            st.add(temp);
        }
        else if (oper == "exists")
        {
            if (st.exists(temp))
                cout << "true" << endl;
            else
                cout << "false" << endl;
        }
        else
        {
            st.rmove(temp);
        }
    }
}



#include <iostream>
#include <optional>
#include <list>
#include <vector>
#include <utility>

using namespace std;

class Set
{
public:
    enum class State { EMPTY, FULL, RIP };

    Set()
    {
        a.resize(BASIC_SIZE, {State::EMPTY, 0});
        M = BASIC_SIZE;
        size = 0;
        rip_count = 0;
    }

    void insert(int key)
    {
        size_t i = h(key);
        while (a[i].first != State::EMPTY)
        {
            if (a[i].first == State::FULL && a[i].second == key)
            {
                return;
            }
            i = (i + 1) % M;
        }
        a[i] = { State::FULL, key };
        size++;
    }

    bool exists(int key)
    {
        size_t i = h(key);
        while (a[i].first != State::EMPTY)
        {
            if (a[i].first != State::RIP && a[i].second == key)
            {
                return true;
            }
            i = (i + 1) % M;
        }
        return false;
    }

    void delete_(int key)
    {
        if (!exists(key))
        {
            return;
        }
        size_t i = h(key);
        while (a[i].first != State::EMPTY)
        {
            if (a[i].first != State::RIP && a[i].second == key)
            {
                a[i] = { State::RIP, key };
                rip_count++;
                break;
            }
            i = (i + 1) % M;
        }
        size--;
        if (rip_count + size > M / 2)
        {
            rehash();
        }
    }

private:
    static const size_t BASIC_SIZE = 2'000'000;
    vector<pair<State, int>> a;
    size_t M;
    size_t rip_count;
    size_t size;

    size_t h(int key)
    {
        unsigned long long hash = (((unsigned long long)key * 10657331232548839) % (unsigned long long)1746860020068409) % M;
        return hash;
    }

    void rehash()
    {
        M *= 2;
        vector<pair<State, int>> new_a(M, { State::EMPTY, 0 });
        size = 0;
        rip_count = 0;

        for (const auto& iter : a)
        {
            size_t i = h(iter.second);
            while (new_a[i].first != State::EMPTY)
            {
                i = (i + 1) % M;
            }
            new_a[i] = { State::FULL, iter.second };
            size++;
        }

        a = new_a;
    }
};
