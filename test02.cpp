#include "heapq.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstdint>

template <typename T>
std::vector<T> distinct(const std::vector<T>& vec) {
  std::vector<T> ret;
  heapq_t<T> h;
  for (const auto& t : vec) {
    h.push(t);
  }

  if (!h.size()) {
    return ret;
  }

  T last = h.pop();
  ret.push_back(last);
  while (h.size()) {
    T x = h.pop();
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
  std::vector<uint32_t> vec;
  for (int i = 0; i < 200; i++) {
    vec.push_back(1 + (i % 7));
  }

  vec = distinct<uint32_t>(vec);
  for (auto x: vec) {
    printf("%d\n", x);
  }

  printf("\n");
  printf("#distinct = %d\n", (int)vec.size());


  return 0;
}
