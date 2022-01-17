#include <bits/stdc++.h>
using namespace std;

int INIT_SIZE = 100000;
int PRIME = 1304539;
int EMPTY = 0;
int BUSY = 1;
int RIP = 2;



class Set
{


public:


    pair<int, int>* data;
    int cap;
    int ripCnt;
    int elemCnt;
    int hashSeed;


    Set()
    {
        ripCnt = 0;
        elemCnt = 0;
        hashSeed = rand();
        cap = INIT_SIZE;

        data = new pair<int, int>[cap];

        for (int i = 0; i < cap; ++ i)
            data[i] = pair<int, int>(EMPTY, 0);
    }


    int hashFunc(int x)
    {
        return abs(((31 * x * hashSeed) % PRIME) % cap);
    }


    void doRehashing(int newCap)
    {
        hashSeed = rand();
        pair<int, int>* newData = new pair<int, int>[newCap];
        int index, x, stat;

        for (int i = 0; i < cap; ++ i)
        {
            if (data[i].first == BUSY)
            {
                x = data[i].second;
                index = hashFunc(x);

                while (newData[index].first != EMPTY)
                    index = (index + 1) % newCap;

                newData[index] = pair<int, int>(BUSY, x);
            }
        }

        delete[] data;
        data = newData;
        cap = newCap;
        ripCnt = 0;
    }

    void add(int x)
    {
        int index = hashFunc(x);

        while (data[index].first != EMPTY)
        {
            if (data[index].second == x && data[index].first == BUSY)
                return;
            index = (index + 1) % cap;
        }

        data[index] = pair<int, int>(BUSY, x);

        //if ((elemCnt < cap / 4) && elemCnt > cap / 8)
        //    doRehashing(cap / 2);

        if (ripCnt + elemCnt > cap / 4)
            doRehashing(2 * cap);
    }


    void rmove(int x)
    {
        int index = hashFunc(x);

        while (data[index].first != EMPTY)
        {
            if(data[index].second == x && data[index].first != RIP)
            {
                data[index].first = RIP;
                ripCnt++;
                elemCnt--;
                break;
            }
            index = (index + 1) % cap;
        }

        //if ((elemCnt < cap / 4) && elemCnt > cap / 8)
        //    doRehashing(cap / 2);

        if (ripCnt + elemCnt > cap / 4)
            doRehashing(2 * cap);
    }


    bool exists(int x)
    {
        int index = hashFunc(x);

        while (data[index].first != EMPTY)
        {
            if (data[index].second == x && data[index].first == BUSY)
                return true;
            index = (index + 1) % cap;
        }
        return false;
    }
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



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    process();

    return 0;
}






/*void test()
{
    set<int> s1;
    Set s2 = Set();

    string opers[3] = {"insert", "delete", "exists"};
    string oper;
    int elem;
    int temp;

    for (int i = 0; i < 1000; ++ i)
    {
        oper = opers[rand() % 3];
        elem = rand() % 15;

        if (i % 2)
            elem = -1 * elem;

        if (oper == "insert")
        {
            cout << "added  " << elem << endl;
            s2.add(elem);
            s1.insert(elem);
        }
        else if (oper == "exists")
        {
            temp = (s1.find(elem) == s1.end()) ? 0 : 1;
            if (s2.exists(elem) != temp)
                cout << "problem with " << elem << endl;
        }
        else
        {
            cout << elem << "  removed" << endl;
            s2.rmove(elem);
            s1.erase(elem);
        }
    }

}*/




