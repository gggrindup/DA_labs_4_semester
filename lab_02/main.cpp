#include "treap.h"
#include <iostream>
#include <string>

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