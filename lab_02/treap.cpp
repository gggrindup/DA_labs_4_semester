#include "treap.h"
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