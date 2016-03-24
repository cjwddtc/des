#include <functional>
#include <map>
#include <stdio.h>
#include <time.h>
#include <vector>

unsigned char s_array[8][64] = {
    {14, 4,  13, 1, 2,  15, 11, 8,  3,  10, 6,  12, 5,  9,  0, 7,
     4,  1,  14, 8, 13, 6,  2,  11, 15, 12, 9,  7,  3,  10, 5, 0,
     0,  15, 7,  4, 14, 2,  13, 1,  10, 6,  12, 11, 9,  5,  3, 8,
     15, 12, 8,  2, 4,  9,  1,  7,  5,  11, 3,  14, 10, 0,  6, 13},

    {15, 1,  8,  14, 6,  11, 3,  4,  9,  7, 2,  13, 12, 0, 5,  10,
     0,  14, 7,  11, 10, 4,  13, 1,  5,  8, 12, 6,  9,  3, 2,  15,
     3,  13, 4,  7,  15, 2,  8,  14, 12, 0, 1,  10, 6,  9, 11, 5,
     13, 8,  10, 1,  3,  15, 4,  2,  11, 6, 7,  12, 0,  5, 14, 9},

    {10, 0,  9,  14, 6, 3,  15, 5,  1,  13, 12, 7,  11, 4,  2,  8,
     13, 6,  4,  9,  8, 15, 3,  0,  11, 1,  2,  12, 5,  10, 14, 7,
     13, 7,  0,  9,  3, 4,  6,  10, 2,  8,  5,  14, 12, 11, 15, 1,
     1,  10, 13, 0,  6, 9,  8,  7,  4,  15, 14, 3,  11, 5,  2,  12},

    {7,  13, 14, 3, 0,  6,  9,  10, 1,  2, 8, 5,  11, 12, 4,  15,
     10, 6,  9,  0, 12, 11, 7,  13, 15, 1, 3, 14, 5,  2,  8,  4,
     13, 8,  11, 5, 6,  15, 0,  3,  4,  7, 2, 12, 1,  10, 14, 9,
     3,  15, 0,  6, 10, 1,  13, 8,  9,  4, 5, 11, 12, 7,  2,  14},

    {2,  12, 4,  1,  7,  10, 11, 6,  8,  5,  3,  15, 13, 0, 14, 9,
     4,  2,  1,  11, 10, 13, 7,  8,  15, 9,  12, 5,  6,  3, 0,  14,
     14, 11, 2,  12, 4,  7,  13, 1,  5,  0,  15, 10, 3,  9, 8,  6,
     11, 8,  12, 7,  1,  14, 2,  13, 6,  15, 0,  9,  10, 4, 5,  3},

    {12, 1,  10, 15, 9, 2,  6,  8,  0,  13, 3,  4,  14, 7,  5,  11,
     9,  14, 15, 5,  2, 8,  12, 3,  7,  0,  4,  10, 1,  13, 11, 6,
     10, 15, 4,  2,  7, 12, 9,  5,  6,  1,  13, 14, 0,  11, 3,  8,
     4,  3,  2,  12, 9, 5,  15, 10, 11, 14, 1,  7,  6,  0,  8,  13},

    {4,  11, 2,  14, 15, 0, 8,  13, 3,  12, 9, 7,  5,  10, 6, 1,
     1,  4,  11, 13, 12, 3, 7,  14, 10, 15, 6, 8,  0,  5,  9, 2,
     13, 0,  11, 7,  4,  9, 1,  10, 14, 3,  5, 12, 2,  15, 8, 6,
     6,  11, 13, 8,  1,  4, 10, 7,  9,  5,  0, 15, 14, 2,  3, 12},

    {13, 2,  8,  4, 6,  15, 11, 1,  10, 9,  3,  14, 5,  0,  12, 7,
     7,  11, 4,  1, 9,  12, 14, 2,  0,  6,  10, 13, 15, 3,  5,  8,
     1,  15, 13, 8, 10, 3,  7,  4,  12, 5,  6,  11, 0,  14, 9,  2,
     2,  1,  14, 7, 4,  10, 8,  13, 15, 12, 9,  0,  3,  5,  6,  11}};

unsigned char p_box_data[32] = {16, 7, 20, 21, 29, 12, 28, 17, 1,  15, 23,
                                26, 5, 18, 31, 10, 2,  8,  24, 14, 32, 27,
                                3,  9, 19, 13, 30, 6,  22, 11, 4,  25};
unsigned long p_box_array[256][4];
unsigned char extend_data[48] = {0};
unsigned long long extend_array[4][256];
namespace no_use {
template <size_t N> class TYPE {};
template <> class TYPE<32> { typedef unsigned long type; };
template <> class TYPE<64> { typedef unsigned long long type; };
template <> class TYPE<48> { typedef unsigned long long type; };
template <size_t N> using len_type = typename TYPE<N>::type;
template <size_t count, size_t block_size, typename in_type, typename out_type,
          size_t count_ = 0>
struct tran {
  static inline out_type f(in_type in, out_type (*array)[count]) {
    return array[in & ((0x1 << block_size) - 1)][count_] |
           tran<count, block_size, in_type, out_type, count_ + 1>::f(
               in >> block_size, array);
  };
};

template <size_t count, size_t block_size, typename in_type, typename out_type>
struct tran<count, block_size, in_type, out_type, count> {
  static inline out_type f(in_type in, out_type (*array)[count]) { return 0; };
};
}

template <size_t block_size = 8,
          typename in_type = no_use::len_type<block_size << 3>, size_t count,
          typename out_type>
static inline out_type map(in_type in, out_type (*array)[count]) {
  return no_use::tran<count, block_size, in_type, out_type>::f(in, array);
}

// init map by data
template <size_t block_size = 8, size_t count, typename out_type>
static inline void init(std::vector<unsigned char> source,
                        out_type (*map)[count]) {
  std::multimap<unsigned char, unsigned> cache;
  out_type i_;
  for (unsigned i = 0; i < source.size(); i++) {
    cache.insert(std::make_pair(source[i], i - source[i]));
  }
  for (out_type i = 0; i < 256; i++)
    for (unsigned n = 0; n < count; n++)
      for (unsigned j = 0; j < block_size; j++) {
        i_ = i << n * block_size;
        auto pair = cache.equal_range(n * block_size + j);
        for (auto it = pair.first; it != pair.second; it++)
          map[i][n] |= it->second > 0 ? (i_ & 0x1ll << j) << it->second
                                      : (i_ & 0x1ll << j) >> -it->second;
      }
}

int main() {
  unsigned long n;
  unsigned long m;
  unsigned long array[256][4] = {{0}};
  std::vector<unsigned char> qwe;
  init(qwe, array);
  clock_t a = clock();
  for (unsigned long n = 0; n < 0xfffffff; n++)
    m += map(n, array);
  clock_t b = clock();
  printf("%u", b - a, m);
}
