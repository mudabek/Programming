#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;


struct Heap
{
public:
	vector<pair<int, int>> v;
	int operCnt;

	Heap()
	{
        vector<pair<int, int>> v;
        operCnt = 0;
	}

	/* Helper function */
	int parent(int i)
	{
		return (i - 1) / 2;
	}

	int left(int i)
	{
		return (2 * i + 1);
	}

	int right(int i)
	{
		return (2 * i + 2);
	}

	int getKeyIndex(int operNum)
    {
        for (int i = 0; i < v.size(); ++ i)
        {
            if (v[i].second == operNum)
                return i;
        }
        return -1;
    }

    /* Main functions */
	void heapDown(int i)
	{
		int leftCh = left(i);
		int rightCh = right(i);

		int cur = i;

		if (leftCh < v.size() && v[leftCh].first < v[i].first)
			cur = leftCh;

		if (rightCh < v.size() && v[rightCh].first < v[cur].first)
			cur = rightCh;

		if (cur!= i) {
			swap(v[i], v[cur]);
			heapDown(cur);
		}
	}


	void heapUp(int i)
	{
	    if ( i == 0)
            return;

		if (v[parent(i)].first > v[i].first)
		{
			swap(v[i], v[parent(i)]);
			heapUp(parent(i));
		}
	}


	void push(int x)
	{
	    operCnt++;
	    pair<int, int> pr(x, operCnt);
		v.push_back(pr);
		int index = v.size() - 1;
		heapUp(index);
	}


	void getMin()
	{
		if (v.size() == 0)
        {
            cout << "*" << endl;
            return;
        }

        int val = v[0].first;
        int oper = v[0].second;

        v[0] = v.back();
        v.pop_back();

        heapDown(0);

        cout << val << " " << oper << endl;
	}


	void decrKey(int operNum, int value)
    {
        int index = getKeyIndex(operNum);
        if (index == -1)
            return;
        v[index].first = value;
        heapUp(index);
    }
};

void process()
{
    Heap hp = Heap();
    int value;
    int operNum;
    string operation;
    while (cin >> operation)
    {
        if (operation == "push")
        {
            cin >> value;
            hp.push(value);
        }
        else if (operation == "decrease-key")
        {
            cin >> operNum;
            cin >> value;
            hp.decrKey(operNum, value);
        }
        else
        {
            hp.getMin();
        }
    }
}



int main()
{
    process();

    return 0;
}
