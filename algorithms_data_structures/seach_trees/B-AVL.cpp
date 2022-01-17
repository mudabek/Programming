#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int key;
    int height;
    Node* left;
    Node* right;
};

int height(Node* v)
{
    if (v == NULL)
        return 0;
    return v->height;
}

int getBalance(Node* v)
{
    if (v == NULL)
        return 0;
    return height(v->left) - height(v->right);
}

Node* rotateRight(Node* p)
{
    Node* q = p->left;
    Node* t = q->right;

    q->right = p;
    p->left = t;

    p->height = max(height(p->left), height(p->right)) + 1;
    q->height = max(height(q->left), height(q->right)) + 1;

    return q;
}

Node* rotateLeft(Node* p)
{
    Node* q = p->right;
    Node* t = q->left;

    q->left = p;
    p->right = t;

    p->height = max(height(p->left), height(p->right)) + 1;
    q->height = max(height(q->left), height(q->right)) + 1;

    return q;
}

Node* addBalance(int key, Node* v)
{
    v->height = 1 + max(height(v->left), height(v->right));
    int balance = getBalance(v);

    if (balance > 1 && key < v->left->key)
        return rotateRight(v);

    if (balance < -1 && key > v->right->key)
        return rotateLeft(v);

    if (balance > 1 && key > v->left->key)
    {
        v->left = rotateLeft(v->left);
        return rotateRight(v);
    }
    if (balance < -1 && key < v->right->key)
    {
        v->right = rotateRight(v->right);
        return rotateLeft(v);
    }

    return v;
}

Node* add(int key, Node* v)
{
    if (v == NULL)
    {
        Node* newNode = new Node;
        newNode->key = key;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }
    else if (key < v->key)
    {
        v->left = add(key, v->left);
    }
    else if (key > v->key)
    {
        v->right = add(key, v->right);
    }

    return addBalance(key, v);
}

Node* findMax(Node* v)
{
    while (v->right != NULL)
        v = v->right;
    return v;
}

Node* remvBalance(Node* v)
{
    v->height = 1 + max(height(v->left), height(v->right));
    int balance = getBalance(v);

    if (balance > 1 && getBalance(v->left) >= 0)
        return rotateRight(v);

    if (balance < -1 && getBalance(v->right) <= 0)
        return rotateLeft(v);

    if (balance > 1 && getBalance(v->left) < 0)
    {
        v->left = rotateLeft(v->left);
        return rotateRight(v);
    }


    if (balance < -1 && getBalance(v->right) > 0)
    {
        v->right = rotateRight(v->right);
        return rotateLeft(v);
    }

    return v;
}

Node* remv(Node* v, int key)
{
    if (v == NULL)
    {
        return NULL;
    }
    if (key < v->key)
    {
        v->left = remv(v->left, key);
    }
    else if (key > v->key)
    {
        v->right = remv(v->right, key);
    }
    else
    {
        if (v->left == NULL && v->right == NULL && v->key == key)
        {
            Node* temp = v;
            v = NULL;
            delete temp;
        }
        else if (v->left == NULL && v->key == key)
        {
            Node* temp = v;
            v = v->right;
            delete temp;
        }
        else if (v->right == NULL && v->key == key)
        {
            Node* temp = v;
            v = v->left;
            delete temp;
        }
        else if (v->key == key)
        {
            v->key = findMax(v->left)->key;
            v->left = remv(v->left, v->key);
        }
    }

    if (v == NULL)
        return NULL;

    return remvBalance(v);
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

int main()
{
    string oper;
    int key;
    Node* temp;
    Node* root = NULL;

    while (cin >> oper)
    {
        cin >> key;
        if (oper == "insert")
        {
            root = add(key, root);
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
