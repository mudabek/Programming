#include <iostream>
using namespace std;

int MOD = 1000000000;

struct Node
{
    int key;
    int priority;
    Node* left;
    Node* right;
    Node(int k, int p) : key(k), priority(p), left(NULL), right(NULL) {}
};

pair<Node*, Node*> split(Node* v, int key)
{
    if (v == NULL)
    {
        return {NULL, NULL};
    }

    pair<Node*, Node*> result;
    if (v->key > key)
    {
        result = split(v->left, key);
        v->left = result.second;
        return {result.first, v};
    }
    else
    {
        result = split(v->right, key);
        v->right = result.first;
        return {v, result.second};
    }
}

Node* merge(Node* t1, Node* t2)
{
    if (t1 == NULL)
    {
        return t2;
    }
    if (t2 == NULL)
    {
        return t1;
    }
    if (t1->priority > t2->priority)
    {
        t1->right = merge(t1->right, t2);
        return t1;
    }
    else
    {
        t2->left = merge(t1, t2->left);
        return t2;
    }
}

bool exists(int key, Node* v)
{
    if (v == NULL)
    {
        return false;
    }
    if (v->key == key)
    {
        return true;
    }
    else if (key < v->key)
    {
        return exists(key, v->left);
    }
    else
    {
        return exists(key, v->right);
    }
}

Node* next(Node* v, int key)
{
    Node* res = NULL;

    while (v != NULL)
    {
        if (v->key > key)
        {
            res = v;
            v = v->left;
        }
        else
            v = v->right;
    }
    return res;
}



Node* prev(Node* v, int key)
{
    Node* res = NULL;

    while (v != NULL)
    {
        if (v->key < key)
        {
            res = v;
            v = v->right;
        }
        else
            v = v->left;
    }
    return res;
}

Node* add(Node* v, int key, int priority)
{
    if (v == NULL)
    {
        return new Node(key, priority);
    }
    else
    {
        Node* temp = new Node(key, priority);
        pair<Node*, Node*> result = split(v, key);
        Node* t1 = merge(result.first, temp);
        v = merge(t1, result.second);
    }
    return v;
}

Node* remv(Node* v, int key)
{
    if (v == NULL)
    {
        return NULL;
    }
    pair<Node*, Node*> res1 = split(v, key);
    pair<Node*, Node*> res2 = split(res1.first, key - 1);
    v = merge(res2.first, res1.second);
    return v;
}

int main()
{
    string oper;
    int key, priority;
    Node* temp;
    Node* root = NULL;

    while (cin >> oper)
    {
        cin >> key;
        if (oper == "insert")
        {
            priority = rand() % MOD;
            root = add(root, key, priority);
        }
        else if (oper == "delete")
        {
            root = remv(root, key);
        }
        else if (oper == "exists")
        {
            if (exists(key, root))
                cout << "true" << endl;
            else
                cout << "false" << endl;
        }
        else if (oper == "next")
        {
            temp = next(root, key);
            if (temp == NULL)
                cout << "none" << endl;
            else
                cout << temp->key << endl;
        }
        else
        {
            temp = prev(root, key);
            if (temp == NULL)
                cout << "none" << endl;
            else
                cout << temp->key << endl;
        }
    }
    return 0;
}
