#include "heapq.hpp"
#include <cstdio>
#include <cstdlib>

std::vector<int> distinct(const std::vector<int>& vec) {
  std::vector<int> ret;
  heapq_t<int> h;
  for (const auto& t : vec) {
    h.push(t);
  }

  if (!h.size()) {
    return ret;
  }

  int last = h.pop();
  ret.push_back(last);
  while (h.size()) {
    int x = h.pop();
    if (x == last) {
      continue;
    }
    ret.push_back(x);
    last = x;
  }

  return ret;
}

int main()
{
  std::vector<int> vec;
  for (int i = 0; i < 10000; i++) {
    vec.push_back(rand() % 5);
  }

  vec = distinct(vec);
  for (auto x: vec) {
    printf("%d\n", x);
  }


  return 0;
}
