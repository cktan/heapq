#include "heapq.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <nmmintrin.h>

uint32_t crc32c_mix(uint32_t c, const int64_t *data, int len) {
  const char *p = (const char*)&data[0];
  const char *const q = (const char*)&data[len];

  for (; p + 8 < q; p += 8) {
    // 8-byte at a time
    c = (uint32_t)_mm_crc32_u64(c, *(const int64_t *)p);
  }

  for (; p < q; p++) {
    c = _mm_crc32_u8(c, *p);
  }

  return c;
}


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
    int64_t data = 1 + (i % 7);
    auto hash = crc32c_mix(-1, &data, 1);
    printf("%ld %d\n", data, hash);
    vec.push_back(hash);
  }

  vec = distinct<uint32_t>(vec);
  for (auto x: vec) {
    printf("%d\n", x);
  }

  printf("\n");
  printf("#distinct = %d\n", (int)vec.size());


  return 0;
}
