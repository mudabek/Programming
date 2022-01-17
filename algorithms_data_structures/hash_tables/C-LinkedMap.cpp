#include <bits/stdc++.h>
using namespace std;

int CAP = 130000;
int PRIME = 191161;
int PRIME_ALPHA = 31;



struct Node
{
    string key;
    string value;
    Node* next;
    Node* prev;
    Node* nextAdded;
    Node* prevAdded;
};


class LinkedMap
{
public:

    Node** data;
    Node* lastAdded;


    LinkedMap()
    {
        lastAdded = NULL;
        data = new Node*[CAP];

        for (int i = 0; i < CAP; ++ i)
        {
            data[i] = NULL;
        }
    }


    unsigned int hashFunc(string s)
    {
        unsigned int sum = 0;
        int pwr = s.size();

        for (char& c: s)
        {
            sum += (int)c * pow(PRIME_ALPHA, pwr);
            pwr--;
        }

        sum = (sum % PRIME) % CAP;

        return sum;
    }


    void put(string key_, string value_)
    {
        //check if key already exists
        int index = hashFunc(key_);
        Node* cur = data[index];
        while(cur != NULL)
        {
            if (cur->key == key_)
            {
                cur->value = value_;
                delete cur;
                return;
            }
            cur = cur->next;
        }
        delete cur;

        //create a Node and fill out data
        Node* newNode = new Node;
        newNode->key = key_;
        newNode->value = value_;
        newNode->prev = NULL;
        newNode->next = NULL;
        newNode->nextAdded = NULL;

        //update next, prev and lastAdded nodes
        if (lastAdded != NULL)
        {
            newNode->prevAdded = lastAdded;
            lastAdded->nextAdded = newNode;
        }
        else
        {
            newNode->prevAdded = NULL;
        }
        lastAdded = newNode;

        //add data to its proper index
        if (data[index] == NULL)
        {
            data[index] = newNode;
        }
        else
        {
            data[index]->prev = newNode;
            newNode->next = data[index];
            data[index] = newNode;
        }
    }


    Node* getNode(string key_)
    {
        int index = hashFunc(key_);

        Node* cur = data[index];
        while(cur != NULL)
        {
            if (cur->key == key_)
            {
                return cur;
            }
            cur = cur->next;
        }
        return NULL;
    }


    string get(string key_)
    {
        Node* ret = getNode(key_);

        if (ret == NULL)
            return "none";
        else
            return ret->value;
    }


    string prev(string key_)
    {
        Node* ret = getNode(key_);

        if (ret == NULL)
            return "none";
        else
        {
            if (ret->prevAdded == NULL)
                return "none";
            else
            {
                return ret->prevAdded->value;
            }
        }
    }


    string next(string key_)
    {
        Node* ret = getNode(key_);

        if (ret == NULL)
            return "none";
        else
        {
            if (ret->nextAdded == NULL)
                return "none";
            else
                return ret->nextAdded->value;
        }
    }


    void rmve(string key_)
    {
        int index = hashFunc(key_);

        Node* cur = data[index];
        while(cur != NULL)
        {
            if (cur->key == key_)
            {
                //fix prevAdded and nextAdded ordering
                if (cur->prevAdded != NULL && cur->nextAdded != NULL)
                {
                    cur->prevAdded->nextAdded = cur->nextAdded;
                    cur->nextAdded->prevAdded = cur->prevAdded;
                }
                else if (cur->prevAdded != NULL)
                {
                    cur->prevAdded->nextAdded = NULL;
                    lastAdded = cur->prevAdded;
                }
                else if (cur->nextAdded != NULL)
                {
                    cur->nextAdded->prevAdded = NULL;
                }
                else
                {
                    lastAdded = NULL;
                }

                //fix prev and next ordering
                if (cur->prev != NULL && cur->next != NULL)
                {
                    cur->prev->next = cur->next;
                    cur->next->prev = cur->prev;
                }
                else if (cur->prev != NULL)
                {
                    cur->prev->next = NULL;
                }
                else if (cur->next != NULL)
                {
                    data[index] = cur->next;
                }
                else
                {
                    data[index] = NULL;
                }

                delete cur;
                return;
            }
            cur = cur->next;
        }
    }
};


void process()
{
    LinkedMap linkedM = LinkedMap();
    string oper, key, val;


    while (cin >> oper >> key)
    {
        if (oper == "put")
        {
            cin >> val;
            linkedM.put(key, val);
        }
        else if (oper == "get")
        {
            cout << linkedM.get(key) << endl;
        }
        else if (oper == "prev")
        {
            cout << linkedM.prev(key) << endl;
        }
        else if (oper == "next")
        {
            cout << linkedM.next(key) << endl;
        }
        else
        {
            linkedM.rmve(key);
        }
    }
}

int main()
{
    process();
    return 0;
}
