#include <bits/stdc++.h>
using namespace std;


class cyclicDynamicArray
{
public:

    int arrCapacity;
    int* elements;
    int beginIndex;
    int arrSize;


    cyclicDynamicArray()
    {
        elements = new int[1];
        arrCapacity = 1;
        beginIndex = 0;
        arrSize = 0;
    }


    int index(int i)
    {
        return (beginIndex + i) % arrCapacity;
    }


    int get(int x)
    {
        if (x < 0 || x >= arrSize)
            return NULL;
        return elements[index(x)];
    }

    void changeSize (int newCap)
    {
        int* temp = new int[newCap];

        for (int i = 0; i < arrSize; ++ i)
        {
            temp[i] = elements[(beginIndex + i) % arrCapacity];
        }

        delete[] elements;

        arrCapacity = newCap;
        elements = temp;
        temp = nullptr;
        beginIndex = 0;
    }


    void add(int x)
    {
        if ((arrSize + 1) >= arrCapacity)
        {
            changeSize(arrCapacity * 2);
        }

        elements[index(arrSize)] = x;
        arrSize++;
    }


    int removeFirst()
    {
        if (arrSize == 0)
            return NULL;

        int ret = elements[beginIndex];

        if (arrSize - 1 < arrCapacity / 4)
            changeSize(arrCapacity / 2);

        beginIndex = (beginIndex + 1) % arrCapacity;
        arrSize--;

        if (arrSize == 0)
            beginIndex = 0;

        return ret;
    }
};


class Queue
{
public:
    cyclicDynamicArray dynArr;

    Queue()
    {
        dynArr = cyclicDynamicArray();
    }

    void push(int x)
    {
        dynArr.add(x);
    }

    int pop()
    {
        return dynArr.removeFirst();
    }
};


void process(int operations)
{
    char oper;
    int temp;
    Queue que;

    for (int i = 0; i < operations; ++ i)
    {
        cin >> oper;
        if (oper == '+')
        {
            cin >> temp;
            que.push(temp);
        }
        else
        {
            cout << que.pop() << endl;
        }
    }
}


int main()
{
    int operations;

    cin >> operations;

    process(operations);

    return 0;
}
