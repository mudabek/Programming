#include <bits/stdc++.h>
using namespace std;

class Heap
{
public:

    vector<pair<int, int>> elements;
    int operations;

    Heap()
    {
        operations = 0;
        vector<pair<int, int>> elements;
    }


    int getKeyIndex(int operNum)
    {
        for (int i = 0; i < elements.size(); ++ i)
        {
            if (elements[i].second == operNum)
                return i;
        }
        return -1;
    }


    void upHeap(int index)
    {
        if (index == 0)
            return;
        while (index > 0)
        {
            if(elements[index].first < elements[(index - 1) / 2].first)
            {
                swap(elements[index], elements[(index - 1) / 2]);
            }
            index = (index - 1) / 2;
        }
    }


    void add(int x)
    {
        operations = operations + 1;
        pair<int, int> pr(x, operations);
        elements.push_back(pr);
        int i = elements.size() - 1;
        upHeap(i);
    }


    void extractMin()
    {
        operations = operations + 1;
        if (elements.size() == 0)
        {
            cout << "*" << endl;
            return;
        }

        int value = elements[0].first;
        int position = elements[0].second;
        swap(elements[0], elements[elements.size() - 1]);
        elements.pop_back();

        int i = 0;
        while (2 * i + 1 < elements.size())
        {
            int cur = elements[i].first;
            int left = elements[2 * i + 1].first;
            int right;

            if (2 * i + 2 >= elements.size())
                right = INT_MAX;
            else
                right = elements[2 * i + 2].first;

            if (left < cur && left < right)
            {
                swap(elements[i], elements[2 * i + 1]);
                i = 2 * i + 1;
            }
            else if (right < cur)
            {
                swap(elements[i], elements[2 * i + 2]);
                i = 2 * i + 2;
            }
            else
            {
                break;
            }
        }
        cout << value << " " << position << endl;
    }


    void decrKey(int operNum, int value)
    {
        operations = operations + 1;
        int index = getKeyIndex(operNum);
        if (index == -1)
            return;
        elements[index].first = value;
        upHeap(index);
    }
};

void process()
{
    Heap hp = Heap();
    int value, operNum;
    string operation;
    while (cin >> operation)
    {
        if (operation == "push")
        {
            cin >> value;
            hp.add(value);
        }
        else if (operation == "decrease-key")
        {
            cin >> operNum;
            cin >> value;
            hp.decrKey(operNum, value);
        }
        else
        {
            hp.extractMin();
        }
    }
}



int main()
{
    process();

    return 0;
}
