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