#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    int storeMin;
    Node* next;
};


class LinkedList
{
public:

    Node* head;

    LinkedList()
    {
        head = NULL;
    }

    void add(int x)
    {
        Node* newNode = new Node;
        newNode->data = x;
        newNode->next = NULL;


        if(head == NULL)
        {
            head = newNode;
            newNode->storeMin = x;
        }
        else
        {
            newNode->storeMin = x < head->storeMin ? x : head->storeMin;
            newNode->next = head;
            head = newNode;
        }
    }

    void removeHead()
    {
        Node* cur = head;

        if (cur == NULL)
            return;

        if (cur->next == NULL)
        {
            delete cur;
            head = NULL;
            return;
        }

        head = cur->next;
        delete cur;
    }

    int getMin()
    {
        return head->storeMin;
    }
};


class Stack
{
public:
    LinkedList lList;

    Stack()
    {
        lList = LinkedList();
    }

    void push(int x)
    {
        lList.add(x);
    }

    void pop()
    {
        lList.removeHead();
    }

    int getMin()
    {
        return lList.getMin();
    }
};


void process(int numOper)
{
    int temp, i;
    Stack stck = Stack();

    for (i = 0; i < numOper; ++ i)
    {
        scanf("%d", &temp);

        if (temp == 1)
        {
            scanf("%d", &temp);
            stck.push(temp);
        }
        else if (temp == 2)
        {
            stck.pop();
        }
        else
        {
            printf("%d\n", stck.getMin());
        }
    }
}


int main()
{
    int operations;
    scanf("%d", &operations);
    process(operations);
    return 0;
}
