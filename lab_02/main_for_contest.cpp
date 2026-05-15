#pragma once
#include <cstdint>
#include <string>

class Treap {
public:
  Treap();
  ~Treap();

  Treap(const Treap &) = delete;
  Treap &operator=(const Treap &) = delete;

  bool insert(const std::string &key, uint64_t value);
  bool erase(const std::string &key);
  bool find(const std::string &key, uint64_t &out);

private:
  struct Node {
    std::string key;
    uint64_t value;
    int priority;
    Node *left;
    Node *right;

    Node(const std::string &k, uint64_t v, int p);
  };

  Node *root;

  void split(Node *t, const std::string &key, Node *&l, Node *&r);
  Node *merge(Node *l, Node *r);

  Node *insert(Node *t, Node *item);
  Node *erase(Node *t, const std::string &key);
  Node *find(Node *t, const std::string &key);

  static std::string normalize(std::string s);

  void destroy(Node *n);
};

#include <random>

static std::mt19937 rng(712367);

Treap::Node::Node(const std::string &k, uint64_t v, int p)
    : key(k), value(v), priority(p), left(nullptr), right(nullptr) {}

Treap::Treap() : root(nullptr) {}

Treap::~Treap() { destroy(root); }

void Treap::split(Node *t, const std::string &key, Node *&l, Node *&r) {
  if (!t) {
    l = r = nullptr;
    return;
  }

  if (t->key < key) {
    split(t->right, key, t->right, r);
    l = t;
  } else {
    split(t->left, key, l, t->left);
    r = t;
  }
}

Treap::Node *Treap::merge(Node *l, Node *r) {
  if (!l || !r)
    return l ? l : r;

  if (l->priority > r->priority) {
    l->right = merge(l->right, r);
    return l;
  } else {
    r->left = merge(l, r->left);
    return r;
  }
}

Treap::Node *Treap::insert(Node *t, Node *item) {
  if (!t)
    return item;

  if (item->priority > t->priority) {
    split(t, item->key, item->left, item->right);
    return item;
  }

  if (item->key < t->key)
    t->left = insert(t->left, item);
  else if (item->key > t->key)
    t->right = insert(t->right, item);
  else {
    return t;
  }

  return t;
}

Treap::Node *Treap::erase(Node *t, const std::string &key) {
  if (!t)
    return nullptr;

  if (t->key == key) {
    Node *res = merge(t->left, t->right);
    delete t;
    return res;
  }

  if (key < t->key)
    t->left = erase(t->left, key);
  else
    t->right = erase(t->right, key);

  return t;
}

Treap::Node *Treap::find(Node *t, const std::string &key) {
  if (!t)
    return nullptr;

  if (t->key == key)
    return t;

  if (key < t->key)
    return find(t->left, key);
  else
    return find(t->right, key);
}

bool Treap::insert(const std::string &key, uint64_t value) {
  std::string k = normalize(key);

  if (find(root, k))
    return false;

  int pr = rng();
  root = insert(root, new Node(k, value, pr));
  return true;
}

bool Treap::erase(const std::string &key) {
  std::string k = normalize(key);

  if (!find(root, k))
    return false;

  root = erase(root, k);
  return true;
}

bool Treap::find(const std::string &key, uint64_t &out) {
  std::string k = normalize(key);

  Node *res = find(root, k);
  if (!res)
    return false;

  out = res->value;
  return true;
}

std::string Treap::normalize(std::string s) {
  for (char &c : s)
    c = std::tolower(c);
  return s;
}

void Treap::destroy(Node *n) {
  if (!n)
    return;
  destroy(n->left);
  destroy(n->right);
  delete n;
}

#include <iostream>

int main() {
  Treap dict;

  std::string cmd;

  while (std::cin >> cmd) {
    if (cmd == "+") {
      std::string word;
      uint64_t val;
      std::cin >> word >> val;

      if (dict.insert(word, val))
        std::cout << "OK\n";
      else
        std::cout << "Exist\n";
    } else if (cmd == "-") {
      std::string word;
      std::cin >> word;

      if (dict.erase(word))
        std::cout << "OK\n";
      else
        std::cout << "NoSuchWord\n";
    } else {
      std::string word = cmd;
      uint64_t val;

      if (dict.find(word, val))
        std::cout << "OK: " << val << "\n";
      else
        std::cout << "NoSuchWord\n";
    }
  }
}