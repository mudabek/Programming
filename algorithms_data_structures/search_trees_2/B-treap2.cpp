#include <iostream>
using namespace std;

int MOD = 1000000000;

struct Node
{
    int key;
    int priority;
    int cnt;
    Node* left;
    Node* right;
    Node(int k, int p) : key(k), priority(p), left(NULL), right(NULL), cnt(1) {}
};

int getSize(Node* v)
{
    if (v == NULL)
        return 0;
    return v->cnt;
}

void fix(Node* v)
{
    v->cnt = 1 + getSize(v->left) + getSize(v->right);
}

pair<Node*, Node*> split(Node* v, int key)
{
    if (v == NULL)
    {
        return {NULL, NULL};
    }

    pair<Node*, Node*> result;
    if (getSize(v->left) < key)
    {
        result = split(v->right, key - getSize(v->left) - 1);
        v->right = result.first;
        fix(v);
        return {v, result.second};
    }
    else
    {
        result = split(v->left, key);
        v->left = result.second;
        fix(v);
        return {result.first, v};
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
        fix(t1);
        return t1;
    }
    else
    {
        t2->left = merge(t1, t2->left);
        fix(t2);
        return t2;
    }
}

Node* add(Node* v, int i, int key, int priority)
{
    if (v == NULL)
    {
        return new Node(key, priority);
    }
    else
    {
        Node* temp = new Node(key, priority);
        pair<Node*, Node*> res = split(v, i);
        Node* t1 = merge(res.first, temp);
        v = merge(t1, res.second);
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
    pair<Node*, Node*> res2 = split(res1.second, 1);
    v = merge(res1.first, res2.second);
    delete res2.first;
    return v;
}

void print(Node* v)
{
    if (v != NULL)
    {
        if (v->left != NULL)
        {
            print(v->left);
        }

        cout << v->key << " ";

        if (v->right != NULL)
        {
            print(v->right);
        }
    }
}

int main()
{
    string oper;
    int ind, key;
    int arrLen, requests, priority;
    Node* temp;
    Node* root = NULL;

    cin >> arrLen >> requests;

    for (int i = 0; i < arrLen; ++i)
    {
        cin >> key;
        priority = rand() % MOD;
        temp = new Node(key, priority);
        root = merge(root, temp);
    }

    for (int i = 0; i < requests; ++i)
    {
        cin >> oper >> ind;
        if (oper == "del")
        {
            root = remv(root, ind - 1);
        }
        else
        {
            cin >> key;
            priority = rand() % MOD;
            root = add(root, ind, key, priority);
        }
    }

    cout << getSize(root) << endl;
    print(root);
    return 0;
}
