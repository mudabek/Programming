#include <bits/stdc++.h>
using namespace std;

class dynArray
{
public:

    unsigned int arrSize;
    unsigned int arrCapacity;
    int* elements;

    dynArray()
    {
        elements = new int[1];
        arrSize = 0;
        arrCapacity = 1;
    }


    int get(int x)
    {
        if (x < 0 || x >= arrSize)
            return NULL;
        return elements[x];
    }


    void changeCapacity(int newCap)
    {
        arrCapacity = newCap;
        int* newElements = new int[arrCapacity];

        for (int i = 0; i < arrSize; ++ i)
        {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
    }


    void add(int x)
    {
        if ((arrSize + 1) > arrCapacity)
        {
            changeCapacity(2 * arrCapacity);
        }

        elements[arrSize] = x;
        arrSize ++;
    }


    int getLast()
    {
        return elements[arrSize - 1];
    }


    int removeLast()
    {
        int ret = elements[arrSize - 1];
        arrSize--;

        if (arrSize - 1 < arrCapacity / 4)
            changeCapacity(arrCapacity / 2);

        return ret;
    }


    bool isEmpty()
    {
        return (arrSize == 0);
    }
};


class Stack
{
public:

    dynArray arr;

    Stack()
    {
        arr = dynArray();
    }

    void push(int x)
    {
        arr.add(x);
    }

    int top()
    {
        return arr.getLast();
    }

    int pop()
    {
        return arr.removeLast();
    }

    bool isEmpty()
    {
        return arr.isEmpty();
    }

    pair<int, int> doublePop()
    {
        int A = arr.removeLast();
        int B = arr.removeLast();
        pair<int, int> pr (A, B);
        return pr;
    }
};

int calculate(string input)
{
    istringstream ss(input);
    vector<string> data;
    string temp;

    while (ss)
    {
        ss >> temp;
        data.push_back(temp);
    }

    Stack stck = Stack();
    int A, B;

    for (int i = 0; i < data.size() - 1; ++ i)
    {
        if(data[i].compare("+") == 0)
        {
            pair<int, int> pr = stck.doublePop();
            stck.push(pr.first + pr.second);
        }
        else if(data[i].compare("-") == 0)
        {
            pair<int, int> pr = stck.doublePop();
            stck.push(pr.second - pr.first);

        }
        else if(data[i].compare("*") == 0)
        {
            pair<int, int> pr = stck.doublePop();
            stck.push(pr.first * pr.second);
        }
        else
        {
            stck.push(stoi(data[i]));
        }
    }
    return stck.top();
}


int main()
{
    string input;
    getline(cin, input);
    cout << calculate(input);
    return 0;
}
