#include <fstream>
#include <string>
#include <utility>
#include <vector>

const int KEY_LENGTH = 32;
const int KEY_BASE = 16;
const std::string INPUT_FILE_NAME = "input.txt";
const std::string OUTPUT_FILE_NAME = "output.txt";

struct Item {
  std::string key;
  std::string value;
};

int charToInt(char c) {
  if ('0' <= c && c <= '9')
    return c - '0';
  if ('a' <= c && c <= 'z')
    return c - 'a' + 10;
  if ('A' <= c && c <= 'Z')
    return c - 'A' + 10;
  return -1;
}

void count_sort(const std::vector<Item> &arr, std::vector<int> &idx, int pos) {
  int n = idx.size();
  int count[KEY_BASE] = {0};
  std::vector<int> res_idx(n);

  for (int i = 0; i < n; i++) {
    int digit = charToInt(arr[idx[i]].key[pos]);
    count[digit]++;
  }

  for (int i = 1; i < KEY_BASE; i++) {
    count[i] += count[i - 1];
  }

  for (int i = n - 1; i >= 0; i--) {
    int digit = charToInt(arr[idx[i]].key[pos]);
    res_idx[--count[digit]] = idx[i];
  }

  idx = std::move(res_idx);
}

void radix_sort(const std::vector<Item> &arr, std::vector<int> &idx) {
  for (int pos = KEY_LENGTH - 1; pos >= 0; pos--) {
    count_sort(arr, idx, pos);
  }
}

void read_input(std::vector<Item> &arr, std::vector<int> &idx) {
  std::ifstream in(INPUT_FILE_NAME);
  std::string line;

  while (std::getline(in, line)) {
    if (line.empty()) {
      continue;
    }
    size_t tab_pos = line.find('\t');
    arr.push_back({line.substr(0, tab_pos), line.substr(tab_pos + 1)});
  }

  for (int i = 0; i < arr.size(); i++) {
    idx.push_back(i);
  }

  in.close();
}

void write_output(const std::vector<Item> &arr, const std::vector<int> &idx) {
  std::ofstream out(OUTPUT_FILE_NAME);

  for (int i : idx) {
    out << arr[i].key << '\t' << arr[i].value << '\n';
  }

  out.close();
}

int main() {
  std::vector<Item> arr;
  std::vector<int> idx;

  read_input(arr, idx);

  radix_sort(arr, idx);

  write_output(arr, idx);
}