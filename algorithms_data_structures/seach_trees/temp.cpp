#include <algorithm>
#include <iostream>

using namespace std;

struct Node {
  explicit Node(int key) : key(key), left(nullptr), right(nullptr), height(1) {}
  Node* left;
  Node* right;
  int key;
  int height;
};

int get_height(Node* v) {
  if (v == nullptr) {
    return 0;
  }

  return v->height;
}

int get_balance(Node* v) {
  if (v == nullptr) {
    return 0;
  }
  return get_height(v->left) - get_height(v->right);
}

Node* rotate_right(Node* p) {
  Node* q = p->left;
  Node* t = q->right;

  q->right = p;
  p->left = t;

  p->height = max(get_height(p->left), get_height(p->right)) + 1;
  q->height = max(get_height(q->left), get_height(q->right)) + 1;

  return q;
}

Node* rotate_left(Node* p) {
  Node* q = p->right;
  Node* t = q->left;

  q->left = p;
  p->right = t;

  p->height = max(get_height(p->left), get_height(p->right)) + 1;
  q->height = max(get_height(q->left), get_height(q->right)) + 1;

  return q;
}

Node* balance_insert(Node* v, int x) {
  v->height = 1 + max(get_height(v->left), get_height(v->right));
  int balance = get_balance(v);

  if (balance > 1 && x < v->left->key) {
    return rotate_right(v);
  }

  if (balance < -1 && x > v->right->key) {
    return rotate_left(v);
  }

  if (balance > 1 && x > v->left->key) {
    v->left = rotate_left(v->left);
    return rotate_right(v);
  }

  if (balance < -1 && x < v->right->key) {
    v->right = rotate_right(v->right);
    return rotate_left(v);
  }

  return v;
}

Node* insert(Node* v, int x) {
  if (v == nullptr) {
    return new Node(x);
  } else if (x < v->key) {
    v->left = insert(v->left, x);
  } else if (x > v->key) {
    v->right = insert(v->right, x);
  }

  return balance_insert(v, x);
}

Node* exists(Node* v, int x) {
  if (v == nullptr) {
    return nullptr;
  }
  if (v->key == x) {
    return v;
  } else if (x < v->key) {
    return exists(v->left, x);
  } else {
    return exists(v->right, x);
  }
}

Node* get_min_val_node(Node* v) {
  Node* cur = v;
  while (cur && cur->left != nullptr) {
    cur = cur->left;
  }

  return cur;
}

Node* balance_delete(Node* v) {
  v->height = 1 + max(get_height(v->left), get_height(v->right));
  int balance = get_balance(v);

  if (balance > 1 && get_balance(v->left) >= 0) {
    return rotate_right(v);
  }

  if (balance < -1 && get_balance(v->right) <= 0) {
    return rotate_left(v);
  }

  if (balance > 1 && get_balance(v->left) < 0) {
    v->left = rotate_left(v->left);
    return rotate_right(v);
  }

  if (balance < -1 && get_balance(v->right) > 0) {
    v->right = rotate_right(v->right);
    return rotate_left(v);
  }

  return v;
}

Node* delete_(Node* v, int key) {
  if (v == nullptr) {
    return nullptr;
  }
  if (key < v->key) {
    v->left = delete_(v->left, key);
  } else if (key > v->key) {
    v->right = delete_(v->right, key);
  } else {
    if (v->left == nullptr || v->right == nullptr) {
      Node* tmp = v->left ? v->left : v->right;
      if (tmp == nullptr) {
        tmp = v;
        v = nullptr;
      } else {
        *v = *tmp;
      }
      delete tmp;
    } else {
      Node* tmp = get_min_val_node(v->right);
      v->key = tmp->key;
      v->right = delete_(v->right, v->key);
    }
  }

  if (v == nullptr) {
    return nullptr;
  }

  return balance_delete(v);
}

Node* next(Node* v, int key) {
  Node* result = nullptr;
  Node* cur = v;
  while (cur != nullptr) {
    if (cur->key > key) {
      result = cur;
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }

  return result;
}

Node* prev(Node* v, int key) {
  Node* result = NULL;
  Node* cur = v;
  while (cur != NULL) {
    if (cur->key < key) {
      result = cur;
      cur = cur->right;
    } else {
      cur = cur->left;
    }
  }

  return result;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  string op;
  int val;
  Node* root = nullptr;
  Node* tmp = nullptr;
  while (cin >> op) {
    cin >> val;
    if (op == "insert") {
      root = insert(root, val);
    } else if (op == "exists") {
      if (exists(root, val)) {
        cout << "true\n";
      } else {
        cout << "false\n";
      }
    } else if (op == "next") {
      tmp = next(root, val);
      if (tmp) {
        cout << next(root, val)->key << "\n";
      } else {
        cout << "none\n";
      }
    } else if (op == "prev") {
      tmp = prev(root, val);
      if (tmp) {
        cout << prev(root, val)->key << "\n";
      } else {
        cout << "none\n";
      }
    } else if (op == "delete") {
      root = delete_(root, val);
    }
  }

  return 0;
}